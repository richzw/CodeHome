Source:
 
 - [1](https://ieftimov.com/post/make-resilient-golang-net-http-servers-using-timeouts-deadlines-context-cancellation/)
 - [2](https://blog.cloudflare.com/the-complete-guide-to-golang-net-http-timeouts/)

```go
srv := &http.Server{
    ReadTimeout:       1 * time.Second,
    WriteTimeout:      1 * time.Second,
    IdleTimeout:       30 * time.Second,
    ReadHeaderTimeout: 2 * time.Second,
    TLSConfig:         tlsConfig,
    Handler:           srvMux,
}
```

![](https://ieftimov.com/make-resilient-golang-net-http-servers-using-timeouts-deadlines-context-cancellation/request-lifecycle-timeouts.png)

A simple way to think about deadlines is as a point in time at which restrictions on specific actions on the connection are enforced. For example, if we set a write deadline after the deadline time passes, any write actions on the connection will be forbidden.

While we can create timeout-like behavior using deadlines, we cannot control the time it takes for our handlers to complete. Deadlines operate on the connection, so our server will fail to return a result only after the handlers try to access connection properties (such as writing to http.ResponseWriter).

Exposed by `net.Conn` with the `Set[Read|Write]Deadline(time.Time)` methods, Deadlines are an absolute time which when reached makes all I/O operations fail with a timeout error.

**Deadlines are not timeouts**. Once set they stay in force forever (or until the next call to SetDeadline), no matter if and how the connection is used in the meantime. So to build a timeout with SetDeadline you'll have to call it before every Read/Write operation

server timeout
======

![](https://blog.cloudflare.com/content/images/2016/06/Timeouts-001.png)

client timeout
======

![](https://blog.cloudflare.com/content/images/2016/06/Timeouts-002.png)


