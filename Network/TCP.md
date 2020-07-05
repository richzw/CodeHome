
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

