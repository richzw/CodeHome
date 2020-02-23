// https://blog.csdn.net/xuduorui/article/details/78278808

Basic info
----

- 基于HTTP/2 

HTTP/2 提供了连接多路复用、双向流、服务器推送、请求优先级、首部压缩等机制。可以节省带宽、降低TCP链接次数、节省CPU，帮助移动设备延长电池寿命等。gRPC 的协议设计上使用了HTTP2 现有的语义，请求和响应的数据使用HTTP Body 发送，其他的控制信息则用Header 表示。

- IDL使用ProtoBuf 

gRPC使用ProtoBuf来定义服务，ProtoBuf是由Google开发的一种数据序列化协议（类似于XML、JSON、hessian）。ProtoBuf能够将数据进行序列化，并广泛应用在数据存储、通信协议等方面。压缩和传输效率高，语法简单，表达力强。

- 多语言支持（C, C++, Python, PHP, Nodejs, C#, Objective-C、Golang、Java） 

HTTP/2 的**多路复用(Multiplexing)** 则允许同时通过单一的 HTTP/2 连接发起多重的请求-响应消息。 
因此 HTTP/2 可以很容易的去实现多流并行而不用依赖建立多个 TCP 连接，HTTP/2 把 HTTP 协议通信的基本单位缩小为一个一个的帧，这些帧对应着逻辑流中的消息。并行地在同一个 TCP 连接上双向交换消息。

![m](https://img-blog.csdn.net/20171019105033713?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveHVkdW9ydWk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

HTTP/2 **传输的数据是二进制的**。相比 HTTP/1.1 的纯文本数据，二进制数据一个显而易见的好处是：更小的传输体积。这就意味着更低的负载。二进制的帧也更易于解析而且不易出错，纯文本帧在解析的时候还要考虑处理空格、大小写、空行和换行等问题，而二进制帧就不存在这个问题

![v](https://img-blog.csdn.net/20171019105519131?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveHVkdW9ydWk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

HTTP是无状态协议。简而言之，这意味着每个请求必须要携带服务器需要的所有细节，而不是让服务器保存住之前请求的元数据。因为http2没有改变这个范式，所以它也需要这样（携带所有细节），因此 HTTP 请求的头部需要包含用于标识身份的数据比如 cookies，而这些数据的量也在随着时间增长。每一个请求的头部都包含这些大量的重复数据，无疑是一种很大的负担。对请求头部进行压缩，将会大大减轻这种负担，尤其对移动端来说，性能提高非常明显。

HTTP/2 使用的**压缩方式是 HPACK**。 http://http2.github.io/http2-spec/compression.html

HTTP2.0在客户端和服务器端使用“首部表”来跟踪和存储之前发送的键-值对，对于相同的数据，不再通过每次请求和响应发送；通信期间几乎不会改变的通用键-值对（用户代理、可接受的媒体类型，等等）只需发送一次。

![d](https://img-blog.csdn.net/20171019105927130?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveHVkdW9ydWk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


HTTP/2 的**服务器推送**所作的工作就是，服务器在收到客户端对某个资源的请求时，会判断客户端十有八九还要请求其他的什么资源，然后一同把这些资源都发送给客户端，即便客户端还没有明确表示它需要这些资源。

客户端可以选择把额外的资源放入缓存中（所以这个特点也叫 Cache push），也可以选择发送一个 RST_STREAM frame 拒绝任何它不想要的资源

![q](https://img-blog.csdn.net/20171019110237588?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveHVkdW9ydWk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


gRPC Pooling
----

From experience, gRPC client connections should be re-used for the lifetime of the client application as they are safe for concurrent use. Furthermore, one of the key features of gRPC is rapid response from remote procedural calls, which would not be achieved if you have to reconnect on every request received.

Nonetheless, it is highly recommended to use some kind of gRPC load balancing along with these persistent connections. Otherwise, a lot of the load may end up on a few long-lived grpc client-server connections. Load Balancing options include:

- A gRPC connection pool on client side combined with a server side TCP (Layer 4) load balancer. This will create a pool of client connections initially, and re-use this pool of connections for subsequent gRPC requests. This is the easier route to implement in my opinion. See Pooling gRPC Connections for an example of grpc connection pooling on grpc client side which uses the [grpc-go-pool](https://github.com/processout/grpc-go-pool) library.
- HTTP/2(Layer 7) load balancer with gRPC support for load balancing requests. See gRPC Load Balancing which gives an overview of different grpc load balancing options. nginx recently added support for gRPC load balancing.

```golang
    var factory grpcpool.Factory
    factory = func() (*grpc.ClientConn, error) {
        conn, err := grpc.Dial(employeeAddr, grpc.WithInsecure())
        if err != nil {
            log.Fatalf("Failed to start gRPC connection: %v", err)
        }
        log.Infof("Connected to employee at %s", employeeAddr)
        return conn, err
    }

    pool, err := grpcpool.New(factory, 5, 5, time.Second)
    if err != nil {
        log.Fatalf("Failed to create gRPC pool: %v", err)
    }

    http.HandleFunc("/power", func(rw http.ResponseWriter, req *http.Request) {
        ...
        ctx := req.Context()
        conn, err := pool.Get(ctx)
        defer conn.Close()
        if err != nil {
            msg := "failed to connect to worker"
            l.Errorln(errors.Wrap(err, msg))

            rw.WriteHeader(http.StatusInternalServerError)
            rw.Write([]byte(msg))
            return
        }
        client := pb.NewWorkerClient(conn)

        workResp, err := client.Work(ctx, &pb.JobRequest{
            Id:       uuid.NewV4().String(),
            Base:     float32(base),
            Exponent: float32(exponent),
        })
        ...
    })
```


gRPC load balance
----

// https://grpc.io/blog/loadbalancing

![](https://user-images.githubusercontent.com/1590890/43815116-a1a3919e-9b00-11e8-855f-69731d2bfb58.png)


缺点：
----

- 1）GRPC尚未提供连接池，需要自行实现 
- 2）尚未提供“服务发现”、“负载均衡”机制 
- 3）因为基于HTTP2，绝大部多数HTTP Server、Nginx都尚不支持，即Nginx不能将GRPC请求作为HTTP请求来负载均衡，而是作为普通的TCP请求。（nginx1.9版本已支持） 
- 4） Protobuf二进制可读性差（貌似提供了Text_Fromat功能） 
默认不具备动态特性（可以通过动态定义生成消息类型或者动态编译支持）

grpc坑：
----

来自https://news.ycombinator.com/item?id=12345223的网友： 
http2只允许单个链接传输10亿流数据。原因在于： 
htt2使用31位整形标示流，服务端使用奇数，客户端使用偶数，所以总共10亿可用。

```
HTTP/2.0 uses an unsigned 31-bit integer to identity individual streams over a connection.
Server-initiated streams must use even identifiers. 
Client-initiated streams must use odd identifiers.
```

解决思路：超过一定数量的流，需要重启链接。

你觉得一个设计RPC框架中最重要的是哪一点？
----

我当时首先说了RPC框架首先是通信、自定义协议（protobuf）、序列化、注册中心。我们的RPC由于C++开发的，只提供消息传输的功能，序列化和协议在应用层做的（主要是考虑不同项目的业务也有区别）。我觉得其中最重要的就是注册中心（数据中心）实现了，这个决定了RPC所能提供扩展功能
