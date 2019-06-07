 https://yq.aliyun.com/articles/257459?spm=a2c4e.11153940.blogcont278922.8.5b91122aruxnuv

具体Redis逐出过期Key的时机为:

- 访问Key时，会判断Key是否过期，逐出过期Key
- CPU空闲时在定期serverCron任务中，逐出部分过期Key
- 每次事件循环执行的时候，逐出部分过期Key

Redis会周期性的随机测试一批设置了过期时间的key并进行处理。测试到的已过期的key将被删除。具体的算法如下:

- Redis配置项hz定义了serverCron任务的执行周期，默认为10，即CPU空闲时每秒执行10次;
- 每次过期key清理的时间不超过CPU时间的25%，即若hz=1，则一次清理时间最大为250ms，若hz=10，则一次清理时间最大为25ms;
- 清理时依次遍历所有的db;
- 从db中随机取20个key，判断是否过期，若过期，则逐出;
- 若有5个以上key过期，则重复步骤4，否则遍历下一个db;
- 在清理过程中，若达到了25%CPU时间，退出清理过程;

这是一个基于概率的简单算法，基本的假设是抽出的样本能够代表整个key空间，redis持续清理过期的数据直至将要过期的key的百分比降到了25%以下。
这也意味着在长期来看任何给定的时刻已经过期但仍占据着内存空间的key的量最多为每秒的写操作量除以4.

- 由于算法采用的随机取key判断是否过期的方式，故几乎不可能清理完所有的过期Key;
- 调高hz参数可以提升清理的频率，过期key可以更及时的被删除，但hz太高会增加CPU时间的消耗;


可选逐出策略如下：

- volatile-lru：从已设置过期时间的数据集（server.db[i].expires）中挑选最近最少使用 的数据淘汰
- volatile-ttl：从已设置过期时间的数据集（server.db[i].expires）中挑选将要过期的数 据淘汰
- volatile-random：从已设置过期时间的数据集（server.db[i].expires）中任意选择数据 淘汰
- allkeys-lru：从数据集（server.db[i].dict）中挑选最近最少使用的数据淘汰
- allkeys-random：从数据集（server.db[i].dict）中任意选择数据淘汰
- no-enviction（驱逐）：禁止驱逐数据
