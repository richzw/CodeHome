/*
1. 将n划分成若干正整数之和的划分数。
2. 将n划分成k个正整数之和的划分数。
3. 将n划分成最大数不超过k的划分数。
4. 将n划分成若干个奇正整数之和的划分数。
5. 将n划分成若干不同整数之和的划分数。
*/

// For question 1
// Integer Partition...
// naive method, recursive version
unsigned long GetPartitionCount(int n, int max){
	if (n == 1 || max == 1)
		return 1;
	else if (n < max)
		return GetPartitionCount(n, n);
	else if (n == max)
		return 1 + GetPartitionCount(n, max-1);
	else
		return GetPartitionCount(n, max-1)+GetPartitionCount(n-max, max);
}

// memorize version
int table[100][100]={0};

int partition(int sum, int largestNumber){
    if (largestNumber==0)
        return 0;
    if (sum==0)
        return 1;
    if (sum<0)
        return 0;

    if (table[sum][largestNumber]!=0)
        return table[sum][largestNumber];

    table[sum][largestNumber]=partition(sum,largestNumber-1) + partition(sum-largestNumber,largestNumber);
    return table[sum][largestNumber];
}

// DP method
/*
1. 将n划分成若干正整数之和的划分数。
2. 将n划分成k个正整数之和的划分数。
3. 将n划分成最大数不超过k的划分数。
4. 将n划分成若干个奇正整数之和的划分数。
5. 将n划分成若干不同整数之和的划分数。
*/
/* Analysis:
1.dp[i][j], divide i into no more than j, count number
	if i < j, dp[i][j] = dp[i][i]
	if i = j, dp[i][j] = 1 + dp[i][j-1]
	if i > j, dp[i][j] = dp[i-j][j] + dp[i][j-1]
	so, dp[i][k] is the answer of question 3.
2.dp[i][j], divide i into the number of integres j.
	if i < j, impossible.
	if i = j, only one case, all numbers are 1, dp[i][j] = 1
	if i < j, case 1, including 1, extract all 1 from j numbers, dp[i-j][j-1].
					  not including 1, equal i-j... j numbers. dp[i-j][j]
		dp[i][j]=dp[i-j][j-1]+dp[i-j][j]
4.f[i][j], all even numbers of division i, g[i][j], all odd numbers of division i
	
5.dp[i][j], divide i into different numbers and no more than j, count number
	if i < j, dp[i][j] = dp[i][j]
	if i = j, dp[i][j] = 1+ dp[i][j-1]
	if i > j, dp[i][j] = dp[i-j][j-1] + dp[i][j-1]
*/
unsigned long GetPartionCount_DP(int n, int k){
    int num[n+1][n+1];                     // num[i][j]表示将i划分为不大于j的划分数
    int num1[n+1][n+1];                     // num1[i][j]表示将i划分为不大于j的不同整数的划分数
    int num2[n+1][n+1];                     // num2[i][j]表示将i划分为j个整数之和的划分数
    int g[n+1][n+1], f[n+1][n+1];          // f[i][j]表示将i划分为j个奇数的划分数,g[i][j]表示将i划分为j个偶数的划分数
 
    for(int i=0; i<=n; i++)
        for(int j=0; j<=n; j++)
            num[i][j]=num1[i][j]=num2[i][j]=f[i][j]=g[i][j]=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++) {
            if(i<j) {
                num[i][j]=num[i][i];
                num1[i][j]=num1[i][i];
                num2[i][j]=0;
            }
            else if(i == j) {
                num[i][j]=1+num[i][j-1];
                num1[i][j]=1+num1[i][j-1];
                num2[i][j]=1;
            }
            else {
                num[i][j]=num[i-j][j]+num[i][j-1];
                num1[i][j]=num1[i-j][j-1]+num1[i][j-1];
                num2[i][j]=num2[i-j][j-1]+num2[i-j][j];
            }
        }
 
    f[0][0]=1; g[0][0]=1;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=i; j++) {
            g[i][j] = f[i-j][j];
            f[i][j] = g[i-j][j] + f[i-1][j-1];
        }
 
    int res1 = num[n][n];
    int res2 = num2[n][k];
    int res3 = num[n][k];
    int res4 = 0;
    for(int i=0; i<=n; i++)
        res4 += f[n][i];
    int res5 = num1[n][n];


}
