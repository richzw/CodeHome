// https://blog.csdn.net/xuduorui/article/details/78278808

Basic info
----

- 基于HTTP/2 

HTTP/2 提供了连接多路复用、双向流、服务器推送、请求优先级、首部压缩等机制。可以节省带宽、降低TCP链接次数、节省CPU，帮助移动设备延长电池寿命等。gRPC 的协议设计上使用了HTTP2 现有的语义，请求和响应的数据使用HTTP Body 发送，其他的控制信息则用Header 表示。

- IDL使用ProtoBuf 

gRPC使用ProtoBuf来定义服务，ProtoBuf是由Google开发的一种数据序列化协议（类似于XML、JSON、hessian）。ProtoBuf能够将数据进行序列化，并广泛应用在数据存储、通信协议等方面。压缩和传输效率高，语法简单，表达力强。

- 多语言支持（C, C++, Python, PHP, Nodejs, C#, Objective-C、Golang、Java） 

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


