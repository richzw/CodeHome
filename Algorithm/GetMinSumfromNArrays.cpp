/*
给定k个数组，每个数组有k个整数。每个数组中选取一个整数，一共k个整数，取其和，一共可以得到k^k个和。
给出方法，求得这k^k个和中，最小的k个。​
​
分析​
大家对于一个有n个元素的数据取前k个算法已经非常熟悉。这个题目也是要取前k个，
但是我们发现求出这k^k个和的时间复杂度已经达到了指数级，这样的算法显然不是我们需要的。​
实际上，可以用多路归并加优先队列来解决这个题目，我们先考虑两个数组，这两个数组里面找到前k个和是比较容易的，
因为我们最终要的是最小的k个和，所以保留k个值就可以了，这个数组是B；
然后三个数组和的前k个值可以基于两个数组前k个和B的基础上来计算出来，这个可以用反证法，
如果三个数组的前k个和中sum是值t和两个数组前k个和B之外的某个值相加得到的
，那么我们就可以找到t+B[1...k]这k个小于sum的k个和，与前提发生冲突，得证。​
依次类推，我们就将原来的问题转化为k-1求两个数组的前k个和的问题。对于两个数组求前k个最小和，
我们可以先将原来的两个数组进行排序，然后采用优先数组来记录前k个和。这部分时间复杂度是O(klogk)
*/

void combineTwoArray(int *a, int* b, int k){
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

	for (int i = 0; i < k; ++i){
		pq.push(make_pair(a[i], i));
	}

	for (int i = 0; i < k; ++i){
		pair<int, int> elem = pq.top();
		pq.pop();
		a[i] = elem.first;
		elem.first = elem.first - b[elem.second] + b[elem.second + 1];
		elem.second++;
		pq.push(elem);
	}
}
