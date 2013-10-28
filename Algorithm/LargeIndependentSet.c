/*


*/

/*
1. dp[0,1][x]表示以节点x为根的子树不取或取x的结果，第一维取0，表示x不在LIS中，第一维取1，表示x在LIS中；​
2. dp[0][leaf]=0，dp[1][leaf]=value of the leaf​
3. dp[0][x]=max of max dp[t=0,1][y is son of x], dp[1][x]=sum of dp[0][y is son of x] + value of x.​
4. 最后取max(dp[0][root],dp[1][root])​
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
