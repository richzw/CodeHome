在Go语言中，每一个goroutine是一个独立的执行单元，相较于每个OS线程固定分配2M内存的模式，goroutine的栈采取了动态扩容方式， 初始时仅为2KB，随着任务执行按需增长，最大可达1GB（64位机器最大是1G，32位机器最大是256M），且完全由golang自己的调度器 Go Scheduler 来调度。此外，GC还会周期性地将不再使用的内存回收，收缩栈空间。 因此，Go程序可以同时并发成千上万个goroutine是得益于它强劲的调度器和高效的内存模型。Go的创造者大概对goroutine的定位就是屠龙刀，因为他们不仅让goroutine作为golang并发编程的最核心组件（开发者的程序都是基于goroutine运行的）而且golang中的许多标准库的实现也到处能见到goroutine的身影，比如net/http这个包，甚至语言本身的组件runtime运行时和GC垃圾回收器都是运行在goroutine上的，作者对goroutine的厚望可见一斑。

任何用户线程最终肯定都是要交由OS线程来执行的，goroutine（称为G）也不例外，但是G并不直接绑定OS线程运行，而是由Goroutine Scheduler中的 P - Logical Processor （逻辑处理器）来作为两者的『中介』，P可以看作是一个抽象的资源或者一个上下文，一个P绑定一个OS线程，在golang的实现里把OS线程抽象成一个数据结构：M，G实际上是由M通过P来进行调度运行的，但是在G的层面来看，P提供了G运行所需的一切资源和环境，因此在G看来P就是运行它的 “CPU”，由 G、P、M 这三种由Go抽象出来的实现，最终形成了Go调度器的基本结构：

- G: 表示Goroutine，每个Goroutine对应一个G结构体，G存储Goroutine的运行堆栈、状态以及任务函数，可重用。G并非执行体，每个G需要绑定到P才能被调度执行。
- P: Processor，表示逻辑处理器， 对G来说，P相当于CPU核，G只有绑定到P(在P的local runq中)才能被调度。对M来说，P提供了相关的执行环境(Context)，如内存分配状态(mcache)，任务队列(G)等，P的数量决定了系统内最大可并行的G的数量（前提：物理CPU核数 >= P的数量），P的数量由用户设置的GOMAXPROCS决定，但是不论GOMAXPROCS设置为多大，P的数量最大为256。
- M: Machine，OS线程抽象，代表着真正执行计算的资源，在绑定有效的P后，进入schedule循环；而schedule循环的机制大致是从Global队列、P的Local队列以及wait队列中获取G，切换到G的执行栈上并执行G的函数，调用goexit做清理工作并回到M，如此反复。M并不保留G状态，这是G可以跨M调度的基础，M的数量是不定的，由Go Runtime调整，为了防止创建过多OS线程导致系统调度不过来，目前默认最大限制为10000个。

