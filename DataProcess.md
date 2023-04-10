

- [Petabyte scale data deduplication](https://engineering.mixpanel.com/2019/07/18/petabyte-scale-data-deduplication/)


- Kafka为什么不从读？
  - 1，kafka的分区已经让读是从多个broker读从而负载均衡，不是MySQL的主从，压力都在主上；
  - 2，kafka保存的数据和数据库的性质有实质的区别就是数据具有消费的概念，是流数据，kafka是消息队列，所以消费需要位移，而数据库是实体数据不存在这个概念，如果从kafka的follower读，消费端offset控制更复杂；
  - 3，生产者来说，kafka可以通过配置来控制是否等待follower对消息确认的，如果从上面读，也需要所有的follower都确认了才可以回复生产者，造成性能下降，如果follower出问题了也不好处理

- [Flink 优化](https://mp.weixin.qq.com/s/2OFuyxWN9vyYnpYjmoBbDA)
