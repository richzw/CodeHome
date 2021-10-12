B站
B站一面
gRPC连接的四种模式
简单RPC
服务端流式RPC
客户端流式RPC
双向流式RPC
如何做超时控制
context.WithTimeout/context.WithDeadline + time.After
context.WithTimeout/context.WithDeadline + time.NewTimer
channel + time.After/time.NewTimer
context的实现机制
Redis应用, 页面中有一个活动页的uv人数, 一般使用什么数据类型
set
压缩链表/哈希表(去重)
zset
跳表(主要作用是提高检索效率, 里面的key值是哈希值) + 哈希(去重)
压缩列表(数据量小的时候)
set获取当前元素个数的时间复杂度是多少
O(1)
如果使用bitmap来做去重和uv统计, 是否合理
位数不一定满足
空间利用率可能不高
统计的复杂度是O(N)
MySQL
用户表的建表语句, 包括索引/字段定义
uid的唯一约束
select * from tb_user where uid = xxx for update
uid存在
uid不存在, 间隙锁, 防止幻读的场景, 会锁表
处理方式: 在事务开启之前要保证这条记录存在, 先进行一次搜索, 检查这条记录是否存在
布隆过滤器的问题: 结果不一定准确
update加的是行锁(互斥锁, 不是共享锁)
insert加表锁
innodb引擎的锁机制依赖于什么
加锁机制是针对索引的
user表增加sex字段, 并加索引, 是否会使用索引
不会. 使用索引的话涉及回表, 查出的结果集很大, 每条记录都需要回表, 回表意味着随机IO
IO效率低的原因
寻道时间
旋转时间
10%左右会弃用索引
网络
浏览器中输入网址, 经历了哪些网络过程
TCP为什么需要三次握手
三次握手中能否携带应用层数据(比如HTTP报文)
TCP是双工协议
前两次握手后, 单向通道已经建立, 在第三次握手时就可以携带HTTP报文
HTTP2
HTTP2解决了HTTP中的哪些问题
减小体积, 但是丧失了可读性
解决了慢启动问题
多路复用
设计模式
策略模式
实现斐波那契数列
递归带来函数栈的开销(N^2)
记忆化搜索
B站二面
挑有技术难点的业务项目
介绍下Redis单线程模型是如何运行的, 优缺点
Redis6.0多线程如何实现的?
单线程模型对CPU利用率不高, 如何改造来解决这个问题?
对于SQLselect * from table wher x=1 and y=2 order by z, 如何添加索引
画一下联合索引的节点是如何存储的
介绍一个做过的项目
双端用户, 按用户和商户分库分表, 如果做数据聚合的检索, 如何设计
kafka模型
kafka出现部分节点不可用, 如何设计兜底方案
线上接口超时了, 排查的思路?
币安
币安一面
算法题: 求数组中的最大的unique数
Go服务优雅退出
MySQL什么时候会锁表
锁的类型
表级锁, 开销小, 加锁快, 不会出现死锁
行级锁, 开销大, 加锁慢, 会出现死锁
页面锁
介绍下ACID
原子性
事务隔离
持久性
一致性
介绍Golang CAS
MySQL隔离级别
未提交读
不可重复读
可重复读
串行化
币安二面
自我介绍
算法题
升序二维数组中第K大的元素
getMinRout
Golang GC算法
三色标记的具体过程?
写屏障?
Golang内存分配
TCMalloc 具体?
内存分配的步骤?
线性分配器/空闲链表分配器?
微对象/小对象/大对象 16B, 32KB
Golang GC/GMP模型的演进?
详细描述GMP模型
Goroutine的调度时机
Go关键字
runtime.GoSched
GC
系统调用
内存同步访问(atomic/mutex/channel)
举例哪些操作系统操作会导致的Goroutine抢占
系统调用包括哪些
进程控制
文件管理
设备管理
信息维护
通信
保护
如何完成抢占(抢占的过程)?
抢占是同步还是异步的?
1.14加入了异步抢占
给协程发信号量(UNG的信号量)
g0, g1?
币安三面
自我介绍
简介有技术难点的业务项目
算法
getSubArray
DDD的核心
分库分表的改造
监控
Redis高性能的原因
LRU的实现原理
遇到不熟悉的需求, 怎么处理
方案上有分歧, 怎么处理
可能延期的情况下, 怎么处理
得物
得物一面
Golang和Java相比, 有什么缺点
Java中好的组件如果用Golang迁移, 会有什么问题
如何设计一个Golang DDD微服务框架
如何看点框架化带来的性能损失的问题
Golang/Java/Python中的垃圾回收机制
MySQL B+树, Redis跳表
解释下聚合索引
Golang协程原理
Golang中channel的锁
PostgreSQL与MySQL对比
多租户
得物二面
订单锁的业务场景
使用分布式锁有什么注意点
如何保证cache和db的数据一致性
如何避免缓存击穿
SingleFlight
分布式锁, 不建议, 自研组件很难保证确实只有一个请求进行修改
队列, 回写cache时对队列里的cache miss回写操作, 并检查cache是否已存在, 已存在则跳过
lease
如何解决缓存穿透
如何提升业务稳定性
事前
事后
其他?
限流有哪几种方式
计数器
漏桶
令牌桶算法
Context.WithValue的缺点
Context.Timeout的实现
如何传递超时信号
map是否是并发安全的
介绍CAS
自旋锁和互斥锁的区别
对已关闭的channel进行读写, 是否有问题
可以读, 返回false和或默认值0
写入会直接panic: send on closed channel
Redis的有序集合是如何实现的
跳表 + 哈希
压缩列表
聚簇索引的特点
索引失效有哪些场景
避免or/not in/ != / <> 等操作
使用了SQL内置函数
where子句中order by是否使用了索引
解释下跳表和B+树
得物95线一面
分库分表如何解决查询
Prometheus
Prometheus埋点数据是推还是拉
Golang 高并发设计/调度过程
介绍MySQL事务
MySQL如何修改隔离级别
set global.tx_isolation=’READ-COMMITED’;
或者修改my.cnf文件 transaction-isolation=Read-Committed
Redis数据结构
Redis持久化
Redis中的原子操作有哪些
grpc所使用的网络协议?有哪些
HTTP2是二进制协议, 所以丧失了可读性
HTTP2多路复用, HTTP长连接复用
grpc四种连接方式的区别? server stream和stream rpc的区别?
grpc如何读取/传输数据, 如何保证数据顺序
TapTap
TapTap一面
自我介绍
Golang里做依赖注入 loc
依赖注入的好处是什么
Redis分布式锁
缓存击穿是什么, 如何解决
SingleFlight
分布式锁, 不建议, 自研组件很难保证确实只有一个请求进行修改
队列, 回写cache时对队列里的cache miss回写操作, 并检查cache是否已存在, 已存在则跳过
lease
Redis内存满了会怎么样
Redis配置最大使用内存(配置文件/通过命令实时修改)
LRU内存置换, 通过随机采样法淘汰数据, 每次随机出5个key, 从里面淘汰掉最近最少使用的key. Redis3.0中还会维护一个候选池, 将随机选取的key放入池中, 放满后将访问时间最大的进行移除
如何解决
增加内存
使用内存淘汰策略
Redis集群
Redis缓存淘汰机制
Redis会为每个key中额外增加内存空间用于存储每个key的使用时间, 大小是3字节
Redis4.0中新增LFU算法(最近频繁被使用)
核心思想是根据key最近被访问的频率进行淘汰
六种淘汰策略
默认策略是当内存大小达到阈值, 所有申请内存的指令都会报错
lru(allkeys/volatile)
random(allkeys/volatile)
ttl
如果Redis中的数据有明显的冷热特性, 推荐使用allkeys-lru. 如果所有数据访问频率大致一样, 可以用allkeys-random
Redis删除过期键策略
定时删除, 对内存最友好
惰性删除
定期删除
如何做LRU
Golang GC机制
什么情况下会频繁GC
内存使用量持续增长
小对象分配多
GC的触发机制
手动 runtime.gc()
定期 默认2min触发一次gc
阈值 内存扩大一倍时, 触发
如果优化来减少GC开销
如何让对象创建在栈上而不是堆上
Go语言不同于C, 没有明确的堆栈区分, 具体分配到哪里由编译器自行决定. 一般情况下, 大对象或者存在引用(取地址)的对象会分配在堆上.
反汇编查看内存分配情况
go tool compile -S main.go 分析汇编代码中是否调用了runtime.newobject
逃逸分析
go build -gcflags ‘-m -l’ main.go
Golang内存对齐
协程和线程的区别
为什么内存开销这么大
服务降级
算法题
动规题
GetSteps
top k问题(堆排)
小红书
小红书面经
算法题
LRU
删除链表的倒数第K个节点
Redis Cluster集群出现热点key或者大key怎么办
big key
危害
Redis阻塞, 操作单个big key耗时久, 后面请求会被阻塞
cluster中胡造成内存空间不均匀
过期时可能阻塞
排查: –bigkeys
big key处理
删除bigkey, 异步删除需要Redis4.0支持
拆分
不用Redis, 改MongoDB
热key
如何发现热点
业务经验, 预估
做数据统计, 在客户端进行收集
redis自带的命令 hotkeys/monitor
解决办法
利用二级缓存
备份热key
MySQL什么情况下会锁住整张表
insert时全表锁, 因为要生成主键字段/索引等; update是行级锁
MySQL锁
表级锁
行级锁
页面锁
MySQL的行锁有几种
排它锁
共享锁
MySQL索引, 为什么不适用hashmap
覆盖索引原理, 使用uuid的问题
缓存数据怎么和db保持同步
缓存雪崩/击穿/穿透的解决办法
限流怎么做
计数器
令牌桶算法
漏桶
消息幂等性怎么保证
利用数据库的唯一约束实现幂等
去重表
利用Redis原子性
多版本控制(乐观锁)
乱序消息怎么解决
消息序列号
借鉴TCP中ACK机制, 只有被确认的消息才可以被消费
小红书一面
自我介绍
项目经历, 挑亮点项目
项目业务简介
项目技术架构
主要负责的内容
Golang内存分布
静态区
栈区
堆区
常量区
代码区
Java static关键字
Java GC过程简介
Redis中的数据结构
简单动态字符串
整形数组
压缩列表
双向链表
哈希表
跳表
zset
跳表(主要作用是提高检索效率, 里面的key值是哈希值) + 哈希(去重)
压缩列表(数据量小的时候)
Redis持久化方式
AOF
RDB
Redis4.0混合方式
Redis选举算法?
集群方案: cluster/sentinel
对MVCC的理解
MySQL锁机制
insert上表锁
update上行锁
MySQL中三种log的区别
binlog
二进制数据
MySQL server层实现的
适用于主从同步和数据恢复
redo log
循环队列, 大小固定
innodb引擎独有
适用于crash safe崩溃恢复
undo log
保证原子性, 要么全成功要么全失败
主要记录的是数据的逻辑变化
MVCC多版本实现的关键(并发控制通过锁来实现)
项目中重试/降级/熔断的实现
限流的实现方案
计数器
漏桶算法
令牌桶算法
令牌桶算法的过程
Redis为什么使用跳表而不使用B+树
内存利用率
算法题
动规题
threeSum
UCloud
UCloud一面
自我介绍
项目架构介绍
介绍Golang GMP模型
介绍Golang GC
UCloud二面
自我介绍
Golang和Java对比, 优劣势
线程和Goroutine的区别
早期Goroutine调度存在的问题
全局锁的性能问题
早起是非抢占式调度
操作系统进程的通信方式, 各自的特点是什么
信号量(不适用于网络场景, 需要编程语言的支持)
管道 (适合数据量大的场景)
消息队列
共享内存
亿级大表分库分表介绍
如何防止SQL注入
预编译语句集
使用正则表达式过滤传入的参数
字符串过滤
检查非法字符
GET和POST的区别?
网络传输上有区别吗
GET请求参数长度的限制是哪一端做的
socket
TCP和UDP的区别
死锁是什么, 如何避免(宏观机制)
引起死锁的关键?
Golang中IOTA的原理?
Java中String能否派生类
Golang中接口的推断是静态的还是动态的?
Golang中的error处理
日志如何打
如何串联打日志(调用的链路都能统一打, 标识出来)
日志链路跟踪
运维部署
UCloud三面
自我介绍
如何部署
监控
性能
压测
可观测性
遇到的线上问题, 如何排查, 如何解决的
提交读是否影响性能
Linux如何查看端口是否被占用
lsof
netstat
删文件发现空间未释放
惰性删除
资源未释放
软链
Golang如何限制使用的CPU数量
Golang的core文件如何调试?
算法题
日志文件分析
负责均衡, 一致性哈希
链表反转
触宝
触宝一面
自我介绍
手写Redis实现分布式锁
介绍channel
channel是否线程安全
Golang的GC过程
什么情况下GC压力会比较大, 对服务性能产生影响
Golang常用的包管理方法, 项目结构如何设计
ETCD是否用过
ETCD和zookeeper的异同?
Redis的数据结构有哪几种
Redis事务的执行过程?
Redis哈希的实现原理和时间复杂度
Golang里有哪些锁
互斥锁
读写锁
自旋锁
map是否线程安全
sync.map为什么是线程安全
sync.map的数据结构
Goroutine太多的问题
如何限制Goroutine的数量
操作系统
Linux中软中断机制?
Linux在哪些情况下可能导致CPU物理核的使用不均匀?
Linux单台机器可打开的文件句柄数量是多少, 如何查看, 如何调整?
Linux压缩文件相关的操作
文件如何移动
项目经历
通用能力类的主观问题
遇到过什么线上问题/trouble shouting
多部门协作时困难的点
发现一个功能点不符合预期, 链路比较复杂. 涉及多部门, 如何推进解决
线上反馈的问题, 并不是你own的, 怎么处理 (相关的人又在休假)
如何看待技术视角和产品视角, 怎么理解用户意识和客户意识
项目管理如何做的
在工作中犯过的错误
如何保证线上稳定性
如何实施压测
滴滴
滴滴一面
自我介绍
如何更好的转语言
如何做Java/Golang技术选型, 考虑哪些点
项目经历
MySQL删除时如何释放空间(空间的回收)
微服务和DDD的区别
为何决定使用DDD
架构原则
单一职责
依赖倒置
接口隔离原则, 面向接口而不是依赖实现
开闭原则
里式替换
迪米特法则, 最少知识原则
算法
isValid
twoSum
threeSum
滴滴二面
介绍工作经历, 遇到的挑战
缓存的应用场景, 如何更新
算法题
[]string中第一列升序, 第二列按数字降序排列
follow up, 假设数据量很大, 几百个G的待排数据, 内存只有几个G
map reduce
最近看的技术书籍
Shopee
Shopee一面
自我介绍
算法题
rangeReverse List
时间复杂度分析
如何实现哈希表
进程和线程的区别
进程间的通信方式
多线程情况下, 计数器的实现会存在什么问题
如何保证线程安全
高并发的场景下, 加锁会带来性能开销, 如何解决?
MySQL里的事务用来做什么
MySQL里的索引用来做什么, 为什么要索引, 如何实现, 数据如何组织
抖音首页推荐, 如何保证新的推荐是用户没有看过的
布隆过滤器
Shopee SG一面
自我介绍
算法题
LRU实现
Shopee SG二面
自我介绍
算法题
实现一个HashMap，需要解决哈希冲突
存在的复杂度退化为O(N)的性能问题, 如何解决
Golang hashmap如何实现
Golang Goroutine的实现
Golang如何调度, 如何绑定
MySQL的事务隔离级别
innodb默认隔离级别, 如何实现的
DB follow up问题(略)
唯一ID的生成
UUID
Redis原子操作
雪花算法
业务架构设计
项目架构介绍
GC调优
Shopee SG三面
算法题
找出两个数组中相同的元素
Golang示例代码闭包问题分析, 如何解决
Golang开发过程中遇到的问题(坑)
碰到的性能问题
DB优化
米哈游
米哈游一面
重点项目介绍, 遇到过的问题
如何做容量预估
context包的使用场景
已关闭channel进行读写, nil的channel进行读写
如何限制Goroutine数量
并发读/写是否有问题, 并发append元素是否有问题
哪些场景会导致内存泄漏
聚簇索引/非聚簇索引, 非叶子节点存放的是什么
索引覆盖
悲观锁和乐观锁
表锁/行锁
索引优化
分库分表
Redis锁的弊端
字节
字节一面
自我介绍
业务项目
算法题
前序和中序构建二叉树
字节二面
项目经历
架构设计
算法
字节三面
项目介绍，现场画流程图
算法
地铁寻路/时间统计
美团
美团一面
自我介绍
离职原因
k8s中有哪些网络模式?
k8s CPU使用模式request和limit的区别?
kafka的数据可靠性的保证?
Redis布隆过滤器的使用场景
Redis击破模型?
Redis集群方案, 各自的优点?
cluster, 可扩展性
sentinel, 高可用, master宕机, 自动将slave升级为master
Golang内存逃逸
Goroutine逃逸
字符串截取, 共享内存
子切片引用
函数数组传参时
分库分表方案
业务项目的技术难点
API幂等设计
gRPC的优点?
JSON+gRPC的方案是否可行?
Istio如何实现gRPC流量控制?
HTTP2的特点?
thrift和grpc的对比?
xorm和gorm的对比?
设计一个ORM, 有哪些重要的模块
DB中的一张表在gorm中是什么样的数据结构
MVC和MVP的区别?
gin middleware
鉴权如何实现
腾讯
腾讯电商一面
自我介绍
项目经历, 业务流程/架构简介
BFF是什么, 和网关的区别是什么
Redis哈希是如何实现的
一般来说哈希map有几种实现方式
Redis什么情况下触发渐进式哈希
Redis是否使用集群, 集群如何保证高可用
Redis集群的选举算法?
Redis扩容时如何保证数据的一致性?
Redis集群数据是如何分布的? 如何决定一个key存放在哪个节点上
sharding方式有哪些
Redis大key/热key的解决办法
MySQL事务的隔离级别
未提交读
不可重复读
可重复读
串行化
可重复和不可重复的区别
幻读?
MySQL如何实现可重复读(MVCC)
算法题
三数最接近的target
其他
Golang内存泄漏
Goroutine泄漏
Goroutine栈本身锁占用空间
Goroutine堆的占用空间
如何判断: 检测Goroutine数量, 观察是否持续增长
排查方式
pprof
top
list
traces
监控工具, 观察内存使用量的走势
Prometheus metrics类型
Counter计数器
Gauge仪表盘
histogram和summary 分布数据分布情况
