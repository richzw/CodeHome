Ref: [http://chenzhenianqing.com/articles/1101.html](http://chenzhenianqing.com/articles/1101.html)

```c
unsigned long dictScan(dict *d,
                       unsigned long v,
                       dictScanFunction *fn,
                       void *privdata)
{
    dictht *t0, *t1;
    const dictEntry *de;
    unsigned long m0, m1;

    if (dictSize(d) == 0) return 0;

    if (!dictIsRehashing(d)) {//没有在做rehash，所以只有第一个表有数据的
        t0 = &(d->ht[0]);
        m0 = t0->sizemask;
		//槽位大小-1,因为大小总是2^N,所以sizemask的二进制总是后面都为1,
		//比如16个slot的字典，sizemask为00001111

        /* Emit entries at cursor */
        de = t0->table[v & m0];//找到当前这个槽位，然后处理数据
        while (de) {
            fn(privdata, de);//将这个slot的链表数据全部入队，准备返回给客户端。
            de = de->next;
        }

    } else {
        t0 = &d->ht[0];
        t1 = &d->ht[1];

        /* Make sure t0 is the smaller and t1 is the bigger table */
        if (t0->size > t1->size) {//将地位设置为
            t0 = &d->ht[1];
            t1 = &d->ht[0];
        }

        m0 = t0->sizemask;
        m1 = t1->sizemask;

        /* Emit entries at cursor */
        de = t0->table[v & m0];//处理小一点的表。
        while (de) {
            fn(privdata, de);
            de = de->next;
        }

        /* Iterate over indices in larger table that are the expansion
         * of the index pointed to by the cursor in the smaller table */
        do {//扫描大点的表里面的槽位，注意这里是个循环，会将小表没有覆盖的slot全部扫描一次的
            /* Emit entries at cursor */
            de = t1->table[v & m1];
            while (de) {
                fn(privdata, de);
                de = de->next;
            }

            /* Increment bits not covered by the smaller mask */
			//下面的意思是，还需要扩展小点的表，将其后缀固定，然后看高位可以怎么扩充。
			//其实就是想扫描一下小表里面的元素可能会扩充到哪些地方，需要将那些地方处理一遍。
			//后面的(v & m0)是保留v在小表里面的后缀。
			//((v | m0) + 1) & ~m0) 是想给v的扩展部分的二进制位不断的加1，来造成高位不断增加的效果。
            v = (((v | m0) + 1) & ~m0) | (v & m0);

            /* Continue while bits covered by mask difference is non-zero */
        } while (v & (m0 ^ m1));//终止条件是 v的高位区别位没有1了，其实就是说到头了。
    }

    /* Set unmasked bits so incrementing the reversed cursor
     * operates on the masked bits of the smaller table */
    v |= ~m0;
	//按位取反，其实相当于v |= m0-1 , ~m0也就是11110000,
	//这里相当于将v的不相干的高位全部置为1，待会再进行翻转二进制位，然后加1，然后再转回来

    /* Increment the reverse cursor */
    v = rev(v);
    v++;
    v = rev(v);
	//下面将v的每一位倒过来再加1，再倒回去，这是什么意思呢，
	//其实就是要将有效二进制位里面的高位第一个0位设置置为1，因为现在是0嘛

    return v;
}
```
