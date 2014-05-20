/*
Q:这个LIS问题，可不是Longest Increasing Subsequence，而是Largest Independent Set，
含义如下：给定一棵二叉树，找到满足如下条件的最大节点集合：集合中的任意两个节点之间，都没有边。如下图：​
​        10
     20     30
   40  50      60
      70 80
LIS大小为5，为{10,40,60,70,80}.

通常来讲，树的问题一般都是可以通过递归来解决的。递归是自顶向下的分析问题，分析原问题是否能够分解为子问题。
那么LIS问题呢？我们从LIS集合大小入手，设f(x)为以x为根的数的LIS的大小，根据题目中的定义：​
	1. 当x不在LIS中时，f(x)=sum(所有儿子节点的f(儿子))​
	2. 当x在LIS中的时候，则x的儿子节点肯定不在LIS中，考虑孙子节点，则f(x)=sum(所有孙子节点的f(孙子)) + 1，
	后面的1是x本身。​
上面的描述，转换为代码，很简单。但是效率确实很低，是指数级的。而且，上面的递归过程中，子问题重复的比较多。
最明显的就是，x的儿子节点x的父节点的孙子节点，几乎都要重复计算，所以改进空间很大。
改进的方法，最直接的就是采用缓存将计算过的子问题，缓存起来，待后面直接使用，很简单，却又是非常实用的。​
那么动态规划如何解呢？动态规划是自底向上解决问题，对于上面的递归过程，如何表示x是否在LIS中呢？解法是非常好的:​
	1. dp[0,1][x]表示以节点x为根的子树不取或取x的结果，第一维取0，表示x不在LIS中，第一维取1，表示x在LIS中；​
	2. dp[0][leaf]=0，dp[1][leaf]=value of the leaf​
	3. dp[0][x]=max of max dp[t=0,1][y is son of x], dp[1][x]=sum of dp[0][y is son of x] + value of x.​
	4. 最后取max(dp[0][root],dp[1][root])​
这里比较有意思的是第一维来表示第二维的节点，作为根节点，是否在LIS中。
上面的过程在，前序或者后序的基础之上进行都可以，原则就是一点，有儿子的，就先计算完儿子，再计算父节点。

*/


void get_large_independent_set(int tree[], int len)
{
	int** dp = new int*[2];
	for (int i = 0; i < len; ++i)
		dp[i] = new int[len+1];

	for (int index = 0; index < len; ++index)
	{
		dp[0][index] = 0;
		dp[1][index] = tree[index];
	}

	for (int index = 1; index < len; ++index)
	{
		int left = index*2, right = index*2 + 1;
		int max_child = max(dp[0][left], dp[1][right]); // just use add replace the element collection
		dp[1][index] = tree[index] + dp[0][left] + dp[1][right];

		dp[0][index] = max(max_child, dp[1][index]);
	}

	// the max set is: max(dp[0][1], dp[1][1])
	int max_set = max(dp[0][1], dp[1][1]);
}
