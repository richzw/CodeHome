

The write operation in WiredTiger never updates in-place.

Whenever an operation is issued to WiredTiger, internally it’s broken into multiple transactions wherein
each transaction works within the context of an in-memory snapshot. The snapshot is of the committed
version before the transactions started. Writers can create new versions concurrent with the readers.

The write operations do not change the page; instead the updates are layered on top of the page.

A skipList data structure is used to maintain all the updates, where the most recent update is on the top.
Thus, whenever a user reads/writes the data, the index checks whether a skiplist exists. If a skiplist is not
there, it returns data from the on-disk page image. If skiplist exists, the data at the head of the list is returned
to the threads, which then update the data. Once a commit is performed, the updated data is added to
the head of the list and the pointers are adjusted accordingly. This way multiple users can access data
concurrently without any conflict. The conflict occurs only when multiple threads are trying to update the
same record. In that case, one update wins and the other concurrent update needs to retry.

Any changes to the tree structure due to the update, such as splitting the data if the page sizes increase,
relocation, etc., are later reconciled by a background process. This accounts for the fast write operations of
the WiredTiger engine; the task of data arrangement is left to the background process.

WiredTiger uses the MVCC approach to ensure concurrency control wherein multiple versions of
the data are maintained. It also ensures that every thread that is trying to access the data sees the most
consistent version of the data. As you have seen, the writes are not in place; instead they are appended on
top of the data in a skipList data structure with the most recent update on the top. Threads accessing the
data get the latest copy, and they continue to work with that copy uninterrupted until the time they commit.
Once they commit, the update is appended at the top of the list and thereafter any thread accessing the data
will see that latest update.

This enables multiple threads to access the same data concurrently without any locking or contention.
This also enables the writers to create new versions concurrently with the readers. The conflict occurs only
when multiple threads are trying to update the same record. In that case, one update wins and the other
concurrent update needs to retry.

The WiredTiger journal ensures that writes are persisted to disk between checkpoints. WiredTiger uses
checkpoints to flush data to disk by default every 60 seconds or after 2GB of data has been written. Thus, by
default, WiredTiger can lose up to 60 seconds of writes if running without journaling, although the risk of
this loss will typically be much less if using replication for durability. The WiredTiger transaction log is not
necessary to keep the data files in a consistent state in the event of an unclean shutdown, and so it is safe
to run without journaling enabled, although to ensure durability the “replica safe” write concern should be
configured. Another feature of the WiredTiger storage engine is the ability to compress the journal on disk,
thereby reducing storage space.
