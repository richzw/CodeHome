// https://blog.csdn.net/xuduorui/article/details/78278808

- 基于HTTP/2 

HTTP/2 提供了连接多路复用、双向流、服务器推送、请求优先级、首部压缩等机制。可以节省带宽、降低TCP链接次数、节省CPU，帮助移动设备延长电池寿命等。gRPC 的协议设计上使用了HTTP2 现有的语义，请求和响应的数据使用HTTP Body 发送，其他的控制信息则用Header 表示。

- IDL使用ProtoBuf 

gRPC使用ProtoBuf来定义服务，ProtoBuf是由Google开发的一种数据序列化协议（类似于XML、JSON、hessian）。ProtoBuf能够将数据进行序列化，并广泛应用在数据存储、通信协议等方面。压缩和传输效率高，语法简单，表达力强。

- 多语言支持（C, C++, Python, PHP, Nodejs, C#, Objective-C、Golang、Java） 

![](https://img-blog.csdn.net/20171019113619182?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveHVkdW9ydWk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![](https://img-blog.csdn.net/20171019105033713?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveHVkdW9ydWk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![](https://img-blog.csdn.net/20171019105519131?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveHVkdW9ydWk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

gRPC load balance
// https://grpc.io/blog/loadbalancing


