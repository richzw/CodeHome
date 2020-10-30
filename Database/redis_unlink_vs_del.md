
Is the UNLINK command always better than DEL command?
-----

Before discussing which one is better, let's take a look at the difference between these commands. Both DEL and UNLINK free the key part in blocking mode. And the difference is the way they free the value part.

DEL always frees the value part in blocking mode. However, if the value is too large, e.g. too many allocations for a large LIST or HASH, it blocks Redis for a long time. In order to solve the problem, Redis implements the UNLINK command, i.e. an 'non-blocking' delete.

In fact, UNLINK is NOT always non-blocking/async. If the value is small, e.g. the size of LIST or HASH is less than 64, the value will be freed immediately. In this way, UNLINK is almost the same as DEL, except that it costs a few more function calls than DEL. However, if the value is large, Redis puts the value into a list, and the value will be freed by another thread i.e. the non-blocking free. In this way, the main thread has to do some synchronization with the background thread, and that's also a cost.

In a conclusion, if the value is small, DEL is at least, as good as UNLINK. If value is very large, e.g. LIST with thousands or millions of items, UNLINK is much better than DEL. You can always safely replace DEL with UNLINK. However, if you find the thread synchronization becomes a problem (multi-threading is always a headache), you can rollback to DEL.

Since Redis 6.0, there's a new configuration: lazyfree-lazy-user-del. You can set it to be yes, and Redis will run the DEL command as if running a UNLINK command.


Also, I think the more fast way is we do the decision for redis: using DEL for small key, using UNLINK for a huge key such as big list or set. We can decrease the needless calculation of redis.
