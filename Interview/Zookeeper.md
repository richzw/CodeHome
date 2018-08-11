Ref: 

https://www.itcodemonkey.com/article/6835.html

https://my.oschina.net/xianggao/blog/532010

数据模型
----

- PERSISTENT 持久化节点，节点创建后，不会因为会话失效而消失
- EPHEMERAL 临时节点， 客户端session超时此类节点就会被自动删除
- EPHEMERAL_SEQUENTIAL 临时自动编号节点
- PERSISTENT_SEQUENTIAL 顺序自动编号持久化节点，这种节点会根据当前已存在的节点数自动加 1

监视器 watcher
----

当创建一个节点时，可以注册一个该节点的监视器，当节点状态发生改变时，watch被触发时，ZooKeeper将会向客户端发送且仅发送一条通知，因为watch只能被触发一次。

思路
----

进程需要访问共享数据时, 就在"/lock"节点下创建一个sequence类型的子节点, 称为thisPath. 当thisPath在所有子节点中最小时, 说明该进程获得了锁. 进程获得锁之后, 就可以访问共享资源了. 访问完成后, 需要将thisPath删除. 锁由新的最小的子节点获得.

有了清晰的思路之后, 还需要补充一些细节. 进程如何知道thisPath是所有子节点中最小的呢? 可以在创建的时候, 通过getChildren方法获取子节点列表, 然后在列表中找到排名比thisPath前1位的节点, 称为waitPath, 然后在waitPath上注册监听, 当waitPath被删除后, 进程获得通知, 此时说明该进程获得了锁.

- 创建一个锁目录lock
- 线程A获取锁会在lock目录下，创建临时顺序节点
- 获取锁目录下所有的子节点，然后获取比自己小的兄弟节点，如果不存在，则说明当前线程顺序号最小，获得锁
- 线程B创建临时节点并获取所有兄弟节点，判断自己不是最小节点，设置监听(watcher)比自己次小的节点
- 线程A处理完，删除自己的节点，线程B监听到变更事件，判断自己是最小的节点，获得锁

算法
----

- lock操作过程：

首先为一个lock场景，在zookeeper中指定对应的一个根节点，用于记录资源竞争的内容；

每个lock创建后，会lazy在zookeeper中创建一个node节点，表明对应的资源竞争标识。 (小技巧：node节点为EPHEMERAL_SEQUENTIAL，自增长的临时节点)；

进行lock操作时，获取对应lock根节点下的所有子节点，也即处于竞争中的资源标识；

按照Fair（公平）竞争的原则，按照对应的自增内容做排序，取出编号最小的一个节点做为lock的owner，判断自己的节点id是否就为owner id，如果是则返回，lock成功。

如果自己非owner id，按照排序的结果找到序号比自己前一位的id，关注它锁释放的操作(也就是exist watcher)，形成一个链式的触发过程；

- unlock操作过程：

将自己id对应的节点删除即可，对应的下一个排队的节点就可以收到Watcher事件，从而被唤醒得到锁后退出；

其中的几个**关键点**：

node节点选择为EPHEMERAL_SEQUENTIAL很重要。

自增长的特性，可以方便构建一个基于Fair特性的锁，前一个节点唤醒后一个节点，形成一个链式的触发过程。可以有效的避免"惊群效应"(一个锁释放，所有等待的线程都被唤醒)，有针对性的唤醒，提升性能。

选择一个EPHEMERAL临时节点的特性。因为和zookeeper交互是一个网络操作，不可控因素过多，比如网络断了，上一个节点释放锁的操作会失败。临时节点是和对应的session挂接的，session一旦超时或者异常退出其节点就会消失，类似于ReentrantLock中等待队列Thread的被中断处理。

获取lock操作是一个阻塞的操作，而对应的Watcher是一个异步事件，所以需要使用互斥信号共享锁BooleanMutex进行通知，可以比较方便的解决锁重入的问题。(锁重入可以理解为多次读操作，锁释放为写抢占操作)

**注意**：

使用EPHEMERAL会引出一个风险：在非正常情况下，网络延迟比较大会出现session timeout，zookeeper就会认为该client已关闭，从而销毁其id标示，竞争资源的下一个id就可以获取锁。这时可能会有两个process同时拿到锁在跑任务，所以设置好session timeout很重要。

同样使用PERSISTENT同样会存在一个死锁的风险，进程异常退出后，对应的竞争资源id一直没有删除，下一个id一直无法获取到锁对象。
