
[Source](https://www.cnblogs.com/xiaolincoding/p/12995358.html)

针对增大 TCP 半连接队列和全连接队列的方式如下：
-------

- 增大 TCP 半连接队列的方式是增大 /proc/sys/net/ipv4/tcp_max_syn_backlog；
- 增大 TCP 全连接队列的方式是增大 listen() 函数中的 backlog

![](https://user-images.githubusercontent.com/1590890/86533387-529c3f00-bf03-11ea-878b-4124ceea4351.png) 

不管是半连接队列还是全连接队列，都有最大长度限制，超过限制时，内核会直接丢弃，或返回 RST 包

如何知道应用程序的 TCP 全连接队列大小？
------

ss 命令获取的 Recv-Q/Send-Q 在「LISTEN 状态」和「非 LISTEN 状态」所表达的含义是不同的。

- 在「LISTEN 状态」时，Recv-Q/Send-Q 表示的含义如下：
   - Recv-Q：当前全连接队列的大小，也就是当前已完成三次握手并等待服务端 accept() 的 TCP 连接；
   - Send-Q：当前全连接最大队列长度，上面的输出结果说明监听 8088 端口的 TCP 服务，最大全连接长度为 128；
- 在「非 LISTEN 状态」时，Recv-Q/Send-Q 表示的含义如下
   - Recv-Q：已收到但未被应用进程读取的字节数；
   - Send-Q：已发送但未收到确认的字节数；

模拟全连接队列满

 `wrk -t 6 -c 30000 -d 60s url_host`
 
Linux 有个参数可以指定当 TCP 全连接队列满了会使用什么策略来回应客户端。

`/proc/sys/net/ipv4/tcp_abort_on_overflow`

- 0 ：如果全连接队列满了，那么 server 扔掉 client 发过来的 ack ；
- 1 ：如果全连接队列满了，server 发送一个 reset 包给 client，表示废掉这个握手过程和这个连接 (客户端异常中可以看到很多 connection reset by peer)

通常情况下，应当把 tcp_abort_on_overflow 设置为 0，因为这样更有利于应对突发流量。

举个例子，当 TCP 全连接队列满导致服务器丢掉了 ACK，与此同时，客户端的连接状态却是 ESTABLISHED，进程就在建立好的连接上发送请求。只要服务器没有为请求回复 ACK，请求就会被多次重发。如果服务器上的进程只是短暂的繁忙造成 accept 队列满，那么当 TCP 全连接队列有空位时，再次接收到的请求报文由于含有 ACK，仍然会触发服务器端成功建立连接。

如何增大 TCP 全连接队列呢？
-------

TCP 全连接队列足最大值取决于 `somaxconn` 和 `backlog` 之间的最小值，也就是 `min(somaxconn, backlog)`

- somaxconn 是 Linux 内核的参数，默认值是 128，可以通过 /proc/sys/net/core/somaxconn 来设置其值；
- backlog 是 listen(int sockfd, int backlog) 函数中的 backlog 大小，Nginx 默认值是 511，可以通过修改配置文件设置其长度；

如何查看 TCP 半连接队列长度？
-------

`netstat -natp | grep SYN_RECV | wc -l`

如何模拟 TCP 半连接队列溢出, (所谓的 SYN 洪泛、SYN 攻击、DDos 攻击)

`hping3`

半链接队列大小？

TCP 第一次握手（收到 SYN 包）时会被丢弃的三种条件：

- 如果半连接队列满了，并且没有开启 tcp_syncookies，则会丢弃；
- 若全连接队列满了，且没有重传 SYN+ACK 包的连接请求多于 1 个，则会丢弃；
- 如果没有开启 tcp_syncookies，并且 max_syn_backlog 减去 当前半连接队列长度小于 (max_syn_backlog >> 2)，则会丢弃；

半连接队列最大值不是单单由 max_syn_backlog 决定，还跟 somaxconn 和 backlog 有关系。

- 当 max_syn_backlog > min(somaxconn, backlog) 时， 半连接队列最大值 max_qlen_log = min(somaxconn, backlog) * 2;
- 当 max_syn_backlog < min(somaxconn, backlog) 时， 半连接队列最大值 max_qlen_log = max_syn_backlog * 2;

服务端处于 SYN_RECV 状态的最大个数分为如下两种情况：

- 如果「当前半连接队列」没超过「理论半连接队列最大值」，但是超过 max_syn_backlog - (max_syn_backlog >> 2)，那么处于 SYN_RECV 状态的最大个数就是 max_syn_backlog - (max_syn_backlog >> 2)；
- 如果「当前半连接队列」超过「理论半连接队列最大值」，那么处于 SYN_RECV 状态的最大个数就是「理论半连接队列最大值」；

如果 SYN 半连接队列已满，只能丢弃连接吗
-------

并不是这样，开启 syncookies 功能就可以在不使用 SYN 半连接队列的情况下成功建立连接，在前面我们源码分析也可以看到这点，当开启了 syncookies 功能就不会丢弃连接。

syncookies 是这么做的：服务器根据当前状态计算出一个值，放在己方发出的 SYN+ACK 报文中发出，当客户端返回 ACK 报文时，取出该值验证，如果合法，就认为连接建立成功，如下图所示。





