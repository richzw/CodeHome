/*
1. 将n划分成若干正整数之和的划分数。
2. 将n划分成k个正整数之和的划分数。
3. 将n划分成最大数不超过k的划分数。
4. 将n划分成若干个奇正整数之和的划分数。
5. 将n划分成若干不同整数之和的划分数。
*/

// For question 1
// Integer Partition...
/*
* Counts the number of ways of representing n as a distinct sum of
* positive integers <= max.
* 
* @param n number to sum to
* @param max restriction on the component numbers
* @return number of ways
*/
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
设dp[i][j]为将i划分为不大于j的划分数
(1) 当i<j 时，i不能划分为大于i的数，所以dp[i][j]=dp[i][i]；
(2) 当i>j 时，可以根据划分中是否含有j分为两种情况。若划分中含有j，划分方案数为dp[i-j][j]；
    若划分数中不含j，相当于将i划分为不大于j-1的划分数，为dp[i][j-1]。所以当i>j时dp[i][j]=dp[i-j][j]+dp[i][j-1]；
(3) 当i=j 时，若划分中含有j只有一种情况，若划分中不含j相当于将i划分为不大于j-1的划分数。此时dp[i][j]=1+dp[i][j-1]。	
	
2.dp[i][j], divide i into the number of integres j.
	if i < j, impossible.
	if i = j, only one case, all numbers are 1, dp[i][j] = 1
	if i < j, case 1, including 1, extract all 1 from j numbers, dp[i-j][j-1].
					  not including 1, equal i-j... j numbers. dp[i-j][j]
		dp[i][j]=dp[i-j][j-1]+dp[i-j][j]
设dp[i][j]为将i划分为j个整数的划分数。
　　(1) i<j为不可能出现的情况，dp[i][j]=0；
　　(2) 若i=j，有一种情况：i可以划分为i个1之和，dp[i][j]=1；
　　(3) 若i>j，可以根据划分数中是否含有1分为两类：若划分数中含有1，可以使用“截边法”将j个划分分别截去一个1，
　　    把问题转化为i-j的j-1个划分数，为dp[i-j][j-1]；
　　    若划分中不包含1，使用“截边法”将j个划分数的最下面一个数截去，将为题转化为求i-j的j个划分数，为dp[i-j][j]。
　　    所以i>j时dp[i][j]=dp[i-j][j-1]+dp[i-j][j]。		
		
4.f[i][j], all even numbers of division i, g[i][j], all odd numbers of division i
设f[i][j]为将i划分为j个奇数之和的划分数，g[i][j]为将i划分为j个偶数之和的划分数。
使用截边法，将g[i][j]的j个划分都去掉1，可以得到f[i-j][j]，所以g[i][j] = f[i-j][j]。
f[i][j]中有包含1的划分方案和不包含1的划分方案。对于包含1的划分方案，可以将1的划分除去，
转化为“将i-1划分为j-1个奇数之和的划分数”，即f[i-1][j-1]；
对于不包含1的划分方案，可以使用截边法对j个划分每一个都去掉一个1，转化为“将i-j划分为j个偶数之和的划分数”，即g[i-j][j]。
所以f[i][j]=f[i-1][j-1]+g[i-j][j]。
	
5.dp[i][j], divide i into different numbers and no more than j, count number
	if i < j, dp[i][j] = dp[i][j]
	if i = j, dp[i][j] = 1+ dp[i][j-1]
	if i > j, dp[i][j] = dp[i-j][j-1] + dp[i][j-1]
　　设dp[i][j]为将i划分为不超过j的不同整数的划分数
　　(1) 当i<j时，i不能划分为大于i的数，所以dp[i][j]=dp[i][i]；
　　(2) 当i>j时，可以根据划分中是否含有j分为两种情况。若划分中含有j，则其余的划分中最大只能是j-1，方案数为dp[i-j][j-1]
　　  ；若划分中不含j，相当于将i划分为不大于j-1的划分数，为dp[i][j-1]。所以当i>j时dp[i][j]=dp[i-j][j-1]+dp[i][j-1]；
　　(3) 当i=j时，若划分中含有j只有一种情况，若划分中不含j相当于将i划分为不大于j-1的划分数。此时dp[i][j]=1+dp[i][j-1]	
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
