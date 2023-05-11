Glarity SummaryGlarity Summary
# High Performance Redis

In response to [this brief blog entry](https://wjd.io/2019/03/08/redis-cpu-pinning/), [@antirez tweeted](https://twitter.com/antirez/status/1104075055879864320) for some documentation on high-performance techniques for Redis.  What I present here are general high-performance computing (HPC) techniques.  The examples are oriented to Redis. but they work well for any program designed to be single- or worker-threaded and asynchronous (e.g. uses epoll).

The motivation for using these techniques is to maximize performance of our system and services.  By isolating work, controlling memory, and other tuning, you can achieve significant reduction in latency and increase in throughput.

My perspective comes from the microcosm of my own bare-metal (vs VM), on-premises deployment.  It might not be suitable for all scenarios, especially cloud deployments, as I have little experience with HPC there.  After some discussion, maybe this can be adapted as [redis.io documentation](https://redis.io/documentation).


## The Foot Gun

First of all, remember that "premature optimization is the root of all evil".  And "the leaf of no good" here, is that unless you understand what you are doing, you may actually harm your performance.   The Linux kernel team has spent decades dealing with multi-core process scheduling and other subsystem policies; most of what's written here tosses that aside.

Using HPC techniques &mdash; such CPU pinning with `taskset -c` &mdash; without other system tunings can actually be detrimental to performance.   For example, `taskset -c 1 redis-server`  simply tells the Linux scheduler to only schedule your Redis instance on core #1.   The kernel will do as you command and only let that Redis process run on core #1, *BUT* the kernel's scheduler will also allow other processes to run on that core.  An oversubscribed system might run lots of processes on that core #1, and that poor Redis process has nowhere else to run, impairing its performance.

There are plenty of other ways to do wrong and so much depends on your kernel version, your specific system architecture, and your programs.


## CPU Pinning

CPU Pinning, aka [processor affinity](https://en.wikipedia.org/wiki/Processor_affinity), is telling the kernel's scheduler where you want it to run your processes.  Related to this are Linux [scheduling polcies](https://notes.shichao.io/lkd/ch4/), [`cgroups`](https://en.wikipedia.org/wiki/Cgroups), and [`cpusets`](http://man7.org/linux/man-pages/man7/cpuset.7.html).  Throughout this note, I use the terms "core" and "CPU" interchangeably.

Why would you pin CPUs?  If you knew you had four active Redis processes running continuously churning commands, you could let them all run on specific cores without interrupting each other.  They spend more time doing their work than switching to other CPUs and improves [cache locality](https://en.wikipedia.org/wiki/Locality_of_reference).

One way to do this in Linux is with the [`taskset`](https://linux.die.net/man/1/taskset) command.  The following launches a `redis-server`, forcing it to run only on CPU #1:

```
taskset -c 1 redis-server
```

As we will see, `taskset` is a handy program to get and set processor affinities, but for launching programs the [`numactl`](https://linux.die.net/man/8/numactl) command is preferred.  In addition to its processor affinity arguments, it can also control NUMA policies (discussed below).  Here's the invocation that mimics the `taskset` command above:

```
numactl -all --physcpubind=1 redis-server
```  

The `--all` argument is required because the core is isolated with `isolcpus`, which we discuss in the next section.


## Core Isolation

If you are going to bother to pin a process to a CPU, you probably want to tell the kernel not to schedule anything else there.  This is known as CPU isolation and can be controlled with the [isolcpus boot parameter](https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/cpu-partitioning/isolcpus).  Simply put, `isolcpus` declares which cores are considered in the kernel's scheduling algorithms.   

For our example above, if we want to pin a process to CPU #1, we can tell the kernel not to schedule work there with the boot parameter `isolcpus=1`.

You can easily find out your CPU identifiers like so: `numactl --hardware`:

```
$ numactl --hardware
available: 2 nodes (0-1)
node 0 cpus: 0 2 4 6 8 10
node 0 size: 24189 MB
node 0 free: 8209 MB
node 1 cpus: 1 3 5 7 9 11
node 1 size: 24099 MB
node 1 free: 8389 MB
node distances:
node   0   1 
  0:  10  20 
  1:  20  10 
```

There are a variety of ways to set up a system with `isolcpus`.  Most of my high-performance servers are configured to isolate all cores on a socket, except the first core.  I also have hyperthreading disabled, otherwise I would see twice the number of cpus.  The concept is that each socket has a "dirty" core available for interrupt handling and general system work, and all the other cores have operator-curated process running.  So in this case, I have `isolcpus=2,3,4,5,6,7,8,9,10,11`.

There are other ways to isolate CPUs, such as using `cgroups` and `csets`, but I don't use those except for when configuring Docker (see below).


## NUMA Nodes

In addition to assigning work to CPUs, you can also manage what memory banks your processor uses.  Modern systems use [NUMA memory architecture](https://en.wikipedia.org/wiki/Non-uniform_memory_access).  The general impact of this architecture is that cores can access their own "local" memory faster than it can non-local memory.  Although it can be more complex, for my two-socket systems it means that half the DIMM slots are closer (in latency but you can also see it physically on the motherboard) to one socket than the other half.  Each socket is bound to a "NUMA node"; from my `numactl --hardware` output above, you can see I have two nodes (which map physically to sockets) and core #1 is attached to NUMA node #1.  For core #1 to read memory from NUMA node #0 involves extra latency and other factors.

If I wanted to bind my Redis process to a NUMA node, I would invoke 
`numactl --membind=1 redis-server`  to only allocate memory from NUMA node 1.   `numactl --localalloc` has the same effect without being explicit about the node number; `numactl` knows the system topology so it can pick the node.  

This "localalloc" policy also means that that process only has access to half the memory!  But it is always lowest latency access.   Unless my process has clear memory bounds, I usually use `numactl --preferred=1` which will bias allocations towards NUMA node #1 but still allocate on other nodes if needed.

Putting this all together we get:

```
export REDIS_CPUS=1
numactl --all --physcpubind=$REDIS_CPUS --localalloc redis-server
```

As noted before, the kernel maintainers put work into efficient memory allocation across the system.  Use these techniques carefully as part of a broader performance strategy.


## Docker

Docker allows pinning containers to CPUs and memory allocation [1].  Basically, `--cpuset-cpus` reflects `--physcpubind` and `--cpuset-mems` reflects `--membind`.  

Now using Docker in this way is precarious, which I also [learned the hard way](https://github.com/moby/moby/issues/31086#issuecomment-303744398).  If you specify `isolcpus`, Docker does not honor it because it creates its own `cgroup` across all CPUs.   So `dockerd` itself will run on non-isolated CPUs, but with unmodified configuration, it will allocate work to all CPUs, including your isolated ones.  

Imagine setting up this awesome HPC system and destroying your latency with a simple `docker build .` or `docker run --rm ubuntu echo hello world`?!?

To get around this, I do as I describe [in this issue](https://github.com/moby/moby/issues/31086#issuecomment-323363442):

Create a `cgroup` that explicitly does not include your isolated CPUs, so in my case cores `0,1`:

```
# dockercg_cpus and dockercg_mems are part of my Ansible host variables
#   dockercg_cpus = "0,1"
#   dockercg_cpus = "0,1"
mkdir -p /sys/fs/cgroup/cpuset/dockercg
/bin/echo "{{ dockercg_cpus }}" > /sys/fs/cgroup/cpuset/dockercg/cpuset.cpus
/bin/echo "{{ dockercg_mems }}" > /sys/fs/cgroup/cpuset/dockercg/cpuset.mems
```

Add this `cgroup` to Docker's `daemon.json`:
```
{ "cgroup-parent" : "dockercg" }
```

When I `docker run` with `--cpuset-cpus=<isolated-cores>`, I also add `--cgroup-parent=""` because the new default `cgroup` prevents access to those isolated cores.  Here's the full invocation:

```
export REDIS_CPUS=1
export REDIS_NUMA=1
docker run --cgroup-parent="" --cpuset-cpus=$REDIS_CPUS --cpuset-mems=$REDIS_NUMA redis
```

There's a lot of management involved here, which we deal with using Ansible and Terraform.  The orchestration is a manual curation and some helper scripts -- someday I'd love a Kubernetes Controller to handle this all for me.


## Multi-threaded Redis

OK, I lied before. I said Redis was single-threaded.  Redis is *[indeed multi-threaded](https://redis.io/topics/faq#redis-is-single-threaded-how-can-i-exploit-multiple-cpu--cores)* and in the future will [be even more multi-threaded](http://antirez.com/news/126)!!

So, unless you modify behavior using (`redis.conf`)[http://download.redis.io/redis-stable/redis.conf], simply pinning it to a single core is not a good idea.  Whereas normally, the Linux scheduler would run Redis's threads (which free memory or flush the disk) in parallel with the main thread, the background threads are competing with it &mdash; because you told them to!

So what can you do?  Redis' main thread is also the [primary I/O thread](https://github.com/antirez/redis/blob/b19e8b9a2c84694cd2586983a260ae6dc36afc86/src/server.c#L4897) and all the other threads are for [background tasks](https://github.com/antirez/redis/blob/unstable/src/bio.c#L123).   One approach is to launch Redis bound to a CPU, and then later `taskset` its child threads to another CPU.

This script [`taskset_child_threads.sh`](https://gist.github.com/neomantra/b169ce8d77ad7d70c7d9ee3685384d14) takes a process ID and then `taskset`s all of the children to a given CPU.  So if one wanted to move all the Redis background threads to CPU #2, one could try something like this:

```
MISC_CPUS="10,11"
pgrep redis-server | xargs taskset_child_threads.sh -c $MISC_CPUS
```

Note that I'm letting those background threads, of potentially multiple `redis-server` processes, all run on two isolated cores.  This lets two go in parallel unencumbered by other tasks.   I generally designate a subset of my isolated cores for such purposes.


## Kernel Bypass

So I've talked all about CPU and Memory and Docker setup, which is great....  but here is the secret sauce that makes all this worth it: *kernel bypass*.   I still remember the day in 2011, I was doing bench testing of OpenOnload and realized that two well-tuned, kernel-bypassed systems could pass messages faster over a switch than a single kernel-bound system could pass messages between its cores.  That changed my view of how these HPC systems could be architected.

The benefits of kernel-bypass come from significantly less [context switches](https://en.wikipedia.org/wiki/Context_switch), which are computationally intensive; this also leads better cache locality and other effects.  Kernel-bypass solutions typically include many tunable parameters to optimize performance for the particulars of your program.

My entire on-premise fleet uses [Solarflare's](https://solarflare.com/) network cards combined with their [OpenOnload](https://openonload.org) kernel-bypass solution.  OpenOnload brings the network stack APIs and `epoll` into userspace, along with a lot of tuning variables; it does this using `LD_PRELOAD` and it interoperates extremely well with the Linux kernel.   Using their "TCP and UDP loopback acceleration", same-host communication becomes kernel-free shared memory queues.  This is similar to how you might use UNIX sockets with Redis, but without the kernel involved and happening automagically (OpenOnload detects the loopback, you just configure TCP host and port settings normally).

Since I have Redis running on isolated cores, I am free to use OpenOnload's low-latency mode where it spins constantly in `epoll_wait` with no yielding, userspace TCP networking, and TCP loopback over shared memory.   I can then setup these blazing Redis instances across many cores on a server.   They can work together in Leader/Follower setups or be interconnected to other low-latency services that feed it or read it.  The `PUBLISH` command transforms Redis into a broker of a simple low-latency messaging fabric.

My [primary use case](https://news.ycombinator.com/item?id=14838939) for this is taking the firehose of the US stock market data feeds (many millions of UDP messages per second), convert and embellish the messages to JSON or [flatbuffers](https://github.com/google/flatbuffers), and then invoke combinations Redis `APPEND`, `HSET`, `ZSET` and `PUBLISH` (using modules, but that's another story; also I should look at Streams but haven't).  We pump the day's US stock market depth-of-book and executions into Redis in real-time with low-latency &mdash; the whole market activity becomes an in-memory sea of JSON data, sharded across ~10 Redis instances.

My `tcploop4.opf` OpenOnload profile file looks like this:

```
# TCP loopback acceleration profile
onload_set EF_TCP_SERVER_LOOPBACK 2
onload_set EF_TCP_CLIENT_LOOPBACK 4
```

Here's my full Docker invocation (normally simplified with wrapper scripts):

```
# `neomantra/redis-oo201811` is simply Redis built on top `neomantra/onload:201811-stretch-nozf`
# It is not on Docker Hub, but the Docker base images are.
export DOCKER_IMAGE="neomantra/redis-oo201811"
export REDIS_CPUS=1
export REDIS_NUMA=1
export MISC_CPUS="10,11"

docker run \
    --net=host --device=/dev/onload --device=/dev/onload_epoll --device=/dev/onload_cplane \
    --cgroup-parent="" --cpuset-cpus=$REDIS_CPUS --cpuset-mems=$REDIS_NUMA \
    neomantra/redis-oo201811 \
    /usr/bin/onload -p latency,tcploop4 \
    /usr/local/bin/redis-server -c my_redis.conf

# give time for Redis to start, then taskset Redis' children
sleep 5
pgrep redis-server | xargs taskset_child_threads.sh -c $MISC_CPUS
```

The OpenOnload license doesn't allow benchmarks, but I can say that I get crazy operations/second and scaling consistent with [Solarflare's graphs](https://solarflare.com/wp-content/uploads/2019/02/Redis-Deployment-Guide-Figure-1.png) on [this marketing page](https://solarflare.com/database-caching/); I haven't used as many cores though.  I get 2x to 5x Redis throughput, depending on workload, compared to an untuned setup.


## Interrupts with Kernel Bypass

Once you start isolating cores and mucking with kernel-bypass, then you need to start optimizing your interrupt placements.  You don't want an interrupt to run on your isolated core, blocking work your pinned process could be doing!

This is a whole big topic in itself... maybe [start here](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/6/html/performance_tuning_guide/s-cpu-irq).  Solarflare has a great Low-Latency tuning guide; you need to register to get it.


## Beyond Redis

You can use these techniques for any single-threaded workloads.  I also use these techniques for Nginx/OpenResty, but move worker threads to their own cores.  There's lots of fun to be had with the OpenOnload APIs, if you write network-oriented services.

There's a lot of information out there on how to tune stuff.  Learn, experiment, have fun.  But be careful too!!

----

[1] I had an early [Docker pull request](https://github.com/moby/moby/issues/439) that tried to enable HPC workloads perform on it; I am also still exploring [HPC on Kubernetes](https://github.com/kubernetes/kubernetes/issues/10570#issuecomment-255441875).
