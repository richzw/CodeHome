**gossip协议**

我们的办公室八卦一般都是从一次交谈开始，只要一个人八卦一下，在有限的时间内办公室的的人都会知道该八卦的信息，这种方式也与病毒传播类似。
因此 Gossip也有“病毒感染算法”、“谣言传播算法”之称。

Cassandra，amazon s3，等在使用gossip协议

一般情况是这样的，集群中的节点P随机选择另一个节点Q，两个节点互相交换信息，如果Q有消息需要更新的话，那么Q继续去集群中寻找其他的节点，
再次进行信息的交换，就这样一次次的交换，知道所有的节点消息都为最新的位置.

在Q和P的信息交换，一般有以下3种方式：

- push:P讲信息推送给Q，Q判断是否比本地信息新，如果是的话，更新本地信息
     if P.value.time>Q..value.time
        Q..value = P.value
- pull: P从Q那拉取信息，如果Q的消息比P新，则更新P的消息
     if P.value.time>Q..value.time
        P.value = Q..value
- push-pull: P和Q同时进行Push和pull
     if P.value.time>Q..value.time
        Q..value = P.value
     else
        P.value = Q..value
        
push刚开始传播快，后来慢，pull相反。push-pull模式是最快的

**PAXOS协议**

Paxos算法分为两个阶段。具体如下：

阶段一：

(a) Proposer选择一个提案编号N，然后向半数以上的Acceptor发送编号为N的Prepare请求。

(b) 如果一个Acceptor收到一个编号为N的Prepare请求，且N大于该Acceptor已经响应过的所有Prepare请求的编号，
   那么它就会将它已经接受过的编号最大的提案（如果有的话）作为响应反馈给Proposer，同时该Acceptor承诺不再接受任何编号小于N的提案。

阶段二：

(a) 如果Proposer收到半数以上Acceptor对其发出的编号为N的Prepare请求的响应，那么它就会发送一个针对[N,V]提案的Accept请求给半数以上的Acceptor。
    注意：V就是收到的响应中编号最大的提案的value，如果响应中不包含任何提案，那么V就由Proposer自己决定。

(b) 如果Acceptor收到一个针对编号为N的提案的Accept请求，只要该Acceptor没有对编号大于N的Prepare请求做出过响应，它就接受该提案。

**ZAB协议**

设计目标

- 一致性
- 有序性：有序性是 Zab 协议与 Paxos 协议的一个核心区别。Zab 的有序性主要表现在两个方面：
   a. 全局有序：如果消息 a 在消息 b 之前被投递，那么在任何一台服务器，消息 a都会在消息 b 之前被投递。
   b. 因果有序：如果消息 a 在消息 b 之前发生（a 导致了 b），并被一起发送，则 a 始终在 b 之前被执行。
- 容错性：有 2f+1 台服务器，只要有大于等于 f+1 台的服务器正常工作，就能完全正常工作。

协议内容

Zab 协议分为两大块：

广播（boardcast）：Zab 协议中，所有的写请求都由 leader 来处理。正常工作状态下，leader 接收请求并通过广播协议来处理。

恢复（recovery）：当服务初次启动，或者 leader 节点挂了，系统就会进入恢复模式，直到选出了有合法数量 follower 的新 leader，然后新 leader 
负责将整个系统同步到最新状态。

**raft协议**

leader选举：

leader周期性地heartbeat到所有的follower。follower如果能收到leader发来的消息，那么就保持follower状态。如果follower一段时间收到不消息了
，则开始新的选主。

首先当前term计数加1，然后给自己投票并向其它结点发投票请求。直到以下三种情况：

它赢得选举 另一个服务器成为leader 持续一段时间没有主机胜出

在选主期间，candidate可能收到来自其它自称为leader的写请求，如果该leader的term不小于candidate的当前term，那么candidate承认它是一个合法的
leader并回到follower状态，否则拒绝请求。

如果出现两个candidate得票一样多，则它们都无法获取超过半数投票。这种情况会持续到超时。然后进行新一轮的选举。

使用随机的选举超时，这样不容易发生上面情况。

日志复制

leader收到client写请求后，先写自己的log，然后发到所有服务器，当确认记录已安全复制后，回应client。
每条日志记录会存命令以及term编号，term编号用于检测日志的不一致。
每个提交的记录都是持久的，并且是最终一致的。当log记录成功复投票请求中包含了这个限制：请求中有关于candidate的log信息制到大多数服务器时，记录被提交。
如果投票者的log比它新，则拒绝请求。

