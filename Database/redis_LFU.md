http://mysql.taobao.org/monthly/2018/09/08/

在redis中每个对象都有24 bits空间来记录LRU/LFU信息：

```c
typedef struct redisObject {
    unsigned type:4;
    unsigned encoding:4;
    unsigned lru:LRU_BITS; /* LRU time (relative to global lru_clock) or
                            * LFU data (least significant 8 bits frequency
                            * and most significant 16 bits access time). */
    int refcount;
    void *ptr;
} robj;
```

当这24 bits用作LFU时，其被分为两部分：

- 高16位用来记录访问时间（单位为分钟）
- 低8位用来记录访问频率，简称counter

```
           16 bits         8 bits
      +------------------+--------+
      + Last access time | LOG_C  |
      +------------------+--------+
```

对于counter，redis用了一个trick的手段，counter并不是一个简单的线性计数器，而是用基于概率的对数计数器来实现，算法如下：

```c
  uint8_t LFULogIncr(uint8_t counter) {
      if (counter == 255) return 255;
      double r = (double)rand()/RAND_MAX;
      double baseval = counter - LFU_INIT_VAL;
      if (baseval < 0) baseval = 0;
      double p = 1.0/(baseval*server.lfu_log_factor+1);
      if (r < p) counter++;
      return counter;
  }
 ```
 
对应的概率分布计算公式为：

```
1/((counter-LFU_INIT_VAL)*server.lfu_log_factor+1)
```

从上图可以看到，counter越大，其增加的概率越小，8 bits也足够记录很高的访问频率，下表是不同概率因子server.lfu_log_factor与访问频率counter的对应关系：

```
# +--------+------------+------------+------------+------------+------------+
# | factor | 100 hits   | 1000 hits  | 100K hits  | 1M hits    | 10M hits   |
# +--------+------------+------------+------------+------------+------------+
# | 0      | 104        | 255        | 255        | 255        | 255        |
# +--------+------------+------------+------------+------------+------------+
# | 1      | 18         | 49         | 255        | 255        | 255        |
# +--------+------------+------------+------------+------------+------------+
# | 10     | 10         | 18         | 142        | 255        | 255        |
# +--------+------------+------------+------------+------------+------------+
# | 100    | 8          | 11         | 49         | 143        | 255        |
# +--------+------------+------------+------------+------------+------------+
```

也就是说，默认server.lfu_log_factor为10的情况下，8 bits的counter可以表示1百万的访问频率。

从上一小节的counter增长函数LFULogIncr中我们可以看到，随着key的访问量增长，counter最终都会收敛为255，这就带来一个问题，如果counter只增长不衰减就无法区分热点key。

为了解决这个问题，redis提供了衰减因子server.lfu_decay_time，其单位为分钟，计算方法也很简单，如果一个key长时间没有访问那么它的计数器counter就要减少，减少的值由衰减因子来控制：

```c
unsigned long LFUDecrAndReturn(robj *o) {
    unsigned long ldt = o->lru >> 8;
    unsigned long counter = o->lru & 255;
    unsigned long num_periods = server.lfu_decay_time ? LFUTimeElapsed(ldt) / server.lfu_decay_time : 0;
    if (num_periods)
        counter = (num_periods > counter) ? 0 : counter - num_periods;
    return counter;
}
```

默认为1的情况下也就是N分钟内没有访问，counter就要减N。

redis提供了OBJECT FREQ子命令来获取LFU信息，但是要注意需要先把内存逐出策略设置为allkeys-lfu或者volatile-lfu，否则会返回错误：

```
127.0.0.1:6379> config get maxmemory-policy
1) "maxmemory-policy"
2) "noeviction"
127.0.0.1:6379> object freq counter:000000006889
(error) ERR An LFU maxmemory policy is not selected, access frequency not tracked. Please note that when switching between policies at runtime LRU and LFU data will take some time to adjust.

127.0.0.1:6379> config set maxmemory-policy allkeys-lfu
OK
127.0.0.1:6379> object freq counter:000000006889
(integer) 3
```
