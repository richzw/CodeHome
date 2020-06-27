
Load balance
----

HTTP/1.1 has several features that naturally result in cycling of TCP connections. Because of this, connection-level balancing is "good enough".

gRPC breaks the standard connection-level load balancing, because gRPC is built on HTTP/2, and HTTP/2 is designed to have a single long-lived TCP connection,
across which all requests are multiplexed—meaning multiple requests can be active on the same connection at any point in time. 

in order to do gRPC load balancing, we need to shift from connection balancing to request balancing. In other words, 
we need to open an HTTP/2 connection to each destination, and balance requests across these connections. In network terms, this means we need to make decisions 
at L5/L7 rather than L3/L4.

our application code could manually maintain its own load balancing pool of destinations, and we could configure our gRPC client to use this load balancing pool. 
This approach gives us the most control, but it can be very complex in environments like Kubernetes where the pool changes over time as Kubernetes reschedules pods. Our application would have to watch the Kubernetes API and keep itself up to date with the pods.




[1 gRPC Loading balance](https://kubernetes.io/blog/2018/11/07/grpc-load-balancing-on-kubernetes-without-tears/)
