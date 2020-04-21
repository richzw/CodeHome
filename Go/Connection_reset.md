
The message connection reset by peer indicates that the remote server sent an RST to forcefully close the connection, 
either deliberately as a mechanism to limit connections, or as a result of a lack of resources. 
Either way you are likely opening too many connections, or reconnecting too fast.

Starting 1000-2000 connections in parallel is rarely the most efficient way to download that many pages, 
especially if most or all are coming from a single server. If you test the throughput you will find an optimal concurrency 
level that is far lower.

You will also want to set the Transport.MaxIdleConnsPerHost to match your level of concurrency. 
If MaxIdleConnsPerHost is lower than the expected number of concurrent connections, 
the server connections will often be closed after a request, only to be immediately opened again -- 
this will slow your progress significantly and possibly reach connection limits imposed by the server.

```go
t := &http.Transport{
    Proxy: http.ProxyFromEnvironment,
    DialContext: (&net.Dialer{
        Timeout:   30 * time.Second,
        KeepAlive: 30 * time.Second,
    }).DialContext,
    MaxIdleConnsPerHost:   numCoroutines,
    MaxIdleConns:          100,
    IdleConnTimeout:       90 * time.Second,
    TLSHandshakeTimeout:   10 * time.Second,
    ExpectContinueTimeout: 1 * time.Second,
}
```
