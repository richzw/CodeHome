
// https://www.cnblogs.com/xiaolincoding/p/12995358.html

针对增大 TCP 半连接队列和全连接队列的方式如下：

- 增大 TCP 半连接队列的方式是增大 /proc/sys/net/ipv4/tcp_max_syn_backlog；
- 增大 TCP 全连接队列的方式是增大 listen() 函数中的 backlog

 

