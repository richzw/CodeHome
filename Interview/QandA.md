
- Network 
  - TCP vs UDP
    - ![img.png](network_tcp_vs_udp.png)
  - 流量控制机制 
    - 由接收方控制的、调节发送方生产速度的机制. 
    - 接收能力的变化导致窗口大小的变化，即TCP 流量控制机制
  - 拥塞控制
    - 发送能力的变化导致窗口大小的变化，即 TCP 拥塞控制机制。
    - TCP 不能忽略网络上发生的事，它被设计成一个无私的协议，当网络发送拥塞时，TCP 会自我牺牲，降低发送的数据量。于是，就有了拥塞控制
  - select、poll、epoll区别
    - select
      - select 实现多路复用的方式是，将已连接的 Socket 都放到一个文件描述符集合，然后调用 select 函数将文件描述符集合拷贝到内核里，让内核来检查是否有网络事件产生，检查的方式很粗暴，就是通过遍历文件描述符集合的方式，当检查到有事件产生后，将此 Socket 标记为可读或可写， 接着再把整个文件描述符集合拷贝回用户态里，然后用户态还需要再通过遍历的方法找到可读或可写的 Socket，然后再对其处理。
      - 对于 select 这种方式，需要进行 2 次「遍历」文件描述符集合，一次是在内核态里，一个次是在用户态里 ，而且还会发生 2 次「拷贝」文件描述符集合，先从用户空间传入内核空间，由内核修改后，再传出到用户空间中。
      - select 使用固定长度的 BitsMap，表示文件描述符集合，而且所支持的文件描述符的个数是有限制的，在 Linux 系统中，由内核中的 FD_SETSIZE 限制， 默认最大值为 1024，只能监听 0~1023 的文件描述符。
    - poll
      - poll 不再用 BitsMap 来存储所关注的文件描述符，取而代之用动态数组，以链表形式来组织，突破了 select 的文件描述符个数限制，当然还会受到系统文件描述符限制。
      - poll 和 select 并没有太大的本质区别，都是使用「线性结构」存储进程关注的 Socket 集合，因此都需要遍历文件描述符集合来找到可读或可写的 Socket，时间复杂度为 O(n)，而且也需要在用户态与内核态之间拷贝文件描述符集合
    - epoll
      - epoll 在内核里使用「红黑树」来关注进程所有待检测的 Socket，红黑树是个高效的数据结构，增删改一般时间复杂度是 O(logn)，通过对这棵黑红树的管理，不需要像 select/poll 在每次操作时都传入整个 Socket 集合，减少了内核和用户空间大量的数据拷贝和内存分配。
      - epoll 使用事件驱动的机制，内核里维护了一个「链表」来记录就绪事件，只将有事件发生的 Socket 集合传递给应用程序，不需要像 select/poll 那样轮询扫描整个集合（包含有和无事件的 Socket ），大大提高了检测的效率。
  - 零拷贝
    - sendfile 系统调用实现了零拷贝技术，零拷贝技术的文件传输方式相比传统文件传输的方式，减少了 2 次上下文切换和数据拷贝次数，只需要 2 次上下文切换和数据拷贝次数，就可以完成文件的传输，而且 2 次的数据拷贝过程，都不需要通过 CPU，2 次都是由 DMA 来搬运，使用零拷贝的项目有nginx、kafka。
  - 既然 IP 层会分片，为什么 TCP 层还需要 MSS 呢？
    - MSL 与 TTL 的区别：MSL 的单位是时间，而 TTL 是经过路由跳数。所以 MSL 应该要大于等于 TTL 消耗为 0 的时间，以确保报文已被自然消亡。
    - 那么当如果一个 IP 分片丢失，整个 IP 报文的所有分片都得重传。 因为 IP 层本身没有超时重传机制，它由传输层的 TCP 来负责超时和重传。
    - 经过 TCP 层分片后，如果一个 TCP 分片丢失后，进行重发时也是以 MSS 为单位，而不用重传所有的分片，大大增加了重传的效率。
  - 序列号：
    - 在建立连接时由计算机生成的随机数作为其初始值，通过 SYN 包传给接收端主机，每发送一次数据，就「累加」一次该「数据字节数」的大小。
    - 用来解决网络包乱序问题
  - 确认应答号：
    - 指下一次「期望」收到的数据的序列号，发送端收到这个确认应答以后可以认为在这个序号以前的数据都已经被正常接收。
    - 用来解决不丢包的问题
  -  为什么需要 TIME_WAIT 状态？
    - 主动发起关闭连接的一方，才会有 TIME-WAIT 状态。需要 TIME-WAIT 状态，主要是两个原因：
      - 防止具有相同「四元组」的「旧」数据包被收到
      - 保证「被动关闭连接」的一方能被正确的关闭，即保证最后的 ACK 能让被动关闭方接收，从而帮助其正常关闭
    - TIME_WAIT 过多有什么危害？
      - 如果服务器有处于 TIME-WAIT 状态的 TCP，则说明是由服务器方主动发起的断开请求。过多的 TIME-WAIT 状态主要的危害有两种：
      - 第一是内存资源占用
      - 第二是对端口资源的占用，一个 TCP 连接至少消耗一个本地端口
  - 为什么是三次握手？不是两次、四次？
    - TCP建立连接时，通过三次握手
      - 能防止历史连接的建立
        - 客户端连续发送多次 SYN 建立连接的报文，在网络拥堵情况下：
          - 一个「旧 SYN 报文」比「最新的 SYN 」 报文早到达了服务端 那么此时服务端就会回一个 SYN + ACK 报文给客户端
          - 客户端收到后可以根据自身的上下文，判断这是一个历史连接（序列号过期或超时），那么客户端就会发送 RST 报文给服务端，表示中止这一次连接
      - 能减少双方不必要的资源开销，
        - 如果只有「两次握手」，当客户端的 SYN 请求连接在网络中阻塞，客户端没有接收到 ACK 报文，就会重新发送 SYN ，由于没有第三次握手，服务器不清楚客户端是否收到了自己发送的建立连接的 ACK 确认信号，所以每收到一个 SYN 就只能先主动建立一个连接，这会造成什么情况呢？如果客户端的 SYN 阻塞了，重复发送多次 SYN 报文，那么服务器在收到请求后就会建立多个冗余的无效链接，造成不必要的资源浪费。
      - 能帮助双方同步初始化序列号。 序列号能够保证数据包不重复、不丢弃和按序传
        - TCP 协议的通信双方， 都必须维护一个「序列号」， 序列号是可靠传输的一个关键因素，它的作用：
          - 接收方可以去除重复的数据
          - 接收方可以根据数据包的序列号按序接收
          - 可以标识发送出去的数据包中， 哪些是已经被对方收到的
    - 两次握手：无法防止历史连接的建立，会造成双方资源的浪费，也无法可靠的同步双方序列号
    - 四次握手：三次握手就已经理论上最少可靠连接建立，所以不需要使用更多的通信次数
  - TCP 优化
    - 三次握手
      - SYN重传次数 tcp_sync_retries
      - 绕过三次握手 tcp fastopen
    - 四次挥手
      - FIN重传次数  orphan retries
      - FIN WAIT2的时间（close调用） fin timeout
      - 孤儿链接的上限个数  max orphans

- Mysql
  - MVCC
    - InooDB是通过 MVCC 实现可重复读的隔离级别的，MVCC 就是多版本并发控制，它其实记录了历史版本的数据，解决了读写并发冲突问题。
    - 有一个版本编码，然后它进入了各种操作下的数据状态，能够根据当前这个指令的状态来读取不同时期的数据快照。主要实现方法的话就是通过事务版本号，读取视图还有undo日志进行完善的。
  - 原子性怎么实现的
    - 事务的原子性是通过 undo log 实现的。
    - undo log 是一种用于撤销回退的日志。在事务没提交之前，MySQL 会先记录更新前的数据到 undo log 日志文件里面，当事务回滚时，可以利用 undo log 来进行回滚
  - 持久性是怎么实现的
    - 事务的持久性是通过  redo log  实现的。
    - 我们修改某条记录，其实该记录并不是马上刷入磁盘的，而是将 Innodb 的 Buffer Pool  标记为脏页，等待后续的异步刷盘。
    - InnoDB 引擎会在适当的时候，由后台线程将缓存在 Buffer Pool 的脏页刷新到磁盘里，这就是 WAL （Write-Ahead Logging）技术。
      - WAL 技术指的是， MySQL 的写操作并不是立刻写到磁盘上，而是先写日志，然后在合适的时间再写到磁盘上。
    - redo log 是物理日志，记录了某个数据页做了什么修改，比如对 XXX 表空间中的 YYY 数据页 ZZZ 偏移量的地方做了AAA更新，每当执行一个事务就会产生这样的一条或者多条物理日志。
  - 
 
- 操作系统
  - 死锁
    - 死锁问题的产生是由两个或者以上线程并行执行的时候，争夺资源而互相等待造成的。
    - 死锁只有同时满足互斥、持有并等待、不可剥夺、环路等待这四个条件的时候才会发生。所以要避免死锁问题，就是要破坏其中一个条件即可，最常用的方法就是使用资源有序分配法来破坏环路等待条件。
- 设计一个线程池
- LRU  缓存设计








