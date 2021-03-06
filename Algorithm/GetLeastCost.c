/*
Q:为了修理栅栏，需要将很长的木板锯为N块，长度分别为L1,L2...LN。锯断一块儿木板，需要一定的开销，开销记为木板的长度。
例如，长度为21的木板，锯为三块，长度分别为5，8，8。如下按照如下的顺序据断：
        * 首先锯断21为13和8两块儿，开销为21
        * 然后锯断13为8和5两块儿，开销为13
总的开销为34。但也可以按照如下的顺序：
        * 首先锯断21为16和5两块儿，开销为21
        * 然后锯断16为8和8两块儿，开销为16
总的开销为37。比34要大。问题是，给定N，以及每一块儿的长度。如何保证最小的开销。尽量采用高效的方法。

这个题目，要如何分析？这切锯成N块的方法太多了。如何入手呢？其实，题目中的两个例子，都可以表明，
我们可以将切割的过程用二叉树表示：
            21
        13      8
     8      5
以及
             21
          16      5
       8      8
根据上面两棵二叉树，得到开销的计算方法：
        * 第一棵树，开销34 = 8 * 2 + 5 * 2 + 8 * 1 = 34
        * 第二颗树，开销37 = 8 * 2 + 8 * 2 + 5 * 1 = 37
也就是所有的叶子节点的长度乘以深度。叶子节点，就是各个木块儿的长度。从上面的式子，我们可以得出，要想开销最小，
树的高度是不变的，那就一定要越短的木板，深度越深，即可。而且，因为一次锯开，肯定是两块儿，
所以，要保证整个开销最小，则最短的和次短的木板一定是兄弟，这样，可以递归使得，父亲节点的开销也是最小的。
这样，求的最小开销就很简单了，去最短和次短木板，加起来，得到一个开销，假设L1是最短的，L2是次短的。
则递归处理(L1+L2)以及剩下的木板即可。这个复杂度是O(N^2)的。

那么是否有更高效的方法呢？上面的方法，是从底向上计算的。锯的时候，如何做呢？从最长的开始，每次都把最长的锯掉。
这样排序O(NlogN)。从最大的开始锯。解决。
*/
int compare(const void * a, const void * b){
	return (*(int*)b - *(int*)a);
}

int get_least_cost(int arr[], int len){
	qsort(arr, len, sizeof(int), compare);

	int cost = 0;
	for (int i = 0; i < len; ++i){
		if (i == len-1)
			cost += arr[i]*i;
		else
			cost += arr[i]*(i+1);
	}

	return cost;
}
