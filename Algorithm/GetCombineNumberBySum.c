/*
Q: 求正数数组内和为指定数字的合并总数
比如[5, 5, 10, 2, 3] 合并值为 15 : 有4种 ： (5 + 10, 5 + 10, 5 + 5 + 2 + 3, 10 + 2 + 3)

我们设定f(index，sum)表示数组从index开始到结束组成的sum的总数。那么，f(index, sum)可以表示为什么呢？ 
我们这个题目，就是要最终求得f(0, 15)，从头开始分析，最终组成的和为15的可能组合中，可能包含第0个元素，也可能不包含, 
原始数组为A：
        * 当包含第0个元素时，剩下的表示为f(1, 15-A[0])
        * 不包含第0个元素时，剩下的表示为f(1, 15)
则，f(0, 15) = f(1, 15) + f(1, 15 - A[0])。依次递归。递归的终止条件是什么呢？对于f(index,sum):
        * 当和小于等于0的时候，f(index,sum) = 0
        * 当和小于sum的时候， f(index, sum) = f(index + 1, num);
        * 当和等于sum的时候，f(index, sum) = 1 + f(index + 1, sum);
但是，上面的条件，并没有使用题目中，数组全是正数，也就是存在负数也可以。如果仅仅是正数，后两个改为：
        * 当和小于sum的时候， f(index, sum) = 0;
        * 当和等于sum的时候，f(index, sum) = 1;
有一个条件，我们没有使用，也意味着提升的空间。
可是，上面的方案，时间复杂度是指数级。怎么做一些改进呢？一般在对一个算法进行优化的时候，有哪些思路呢？
尤其是这种时间很恐怖的？我想很多同学都有这个经验，就是空间换时间。
大家可以想象动态规划的思想，大家看如下的状态转移方程：
dp[n][m]=dp[n-1][m]+dp[n-1][m-num[n-1]]
dp[n][m]表示前n个元素组成和为m的情况数。初始化dp[0][0]=1，其他为0。
写出状态转移方程，大家也就明白了，为何要求全是正数了吧，直白一些，数组的索引，怎么可能为负呢？
在计算的过程中，将和的情况保存下来，用空间换时间，整个算法的时间复杂度为O(n*m)，不再是指数级。
*/
int get_combine_number(int arr[], int len, int sum){
	int** dp = new int*[len];
	for (int i = 0; i < len; ++i)
		dp[i] = new int[sum];

	// initialize the dp array
	for (int i = 0; i < len; ++i)
		for (int j = 0; j < sum; ++j)
			dp[i][j] = 0;
	dp[0][0] = 1;

	for (int i = 1; i < len; ++i){
		for (int j = 1; j < sum; ++j){
			if (dp[i][j] != 0)
				dp[i][j] = dp[i-1][j] + dp[i-1][sum-arr[i]];
		}
	}

	int num = 0;
	for (int i = 0; i < len; ++i)
		for (int j = 0; j < sum; ++j)
			if (dp[i][j] > num)
				num = dp[i][j];

	return num;
}
