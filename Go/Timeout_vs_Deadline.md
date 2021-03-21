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

