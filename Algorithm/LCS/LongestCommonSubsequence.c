/*
子问题的递归结构的分析：设序列X=<x1, x2, …, xm>和Y=<y1, y2, …, yn>的一个最长公共子序列Z=<z1, z2, …, zk>，则：
1.  若xm=yn，则zk=xm=yn且Zk-1是Xm-1和Yn-1的最长公共子序列；
2.  若xm≠yn且zk≠xm ，则Z是Xm-1和Y的最长公共子序列；
3.  若xm≠yn且zk≠yn ，则Z是X和Yn-1的最长公共子序列。
其中Xm-1=<x1, x2, …, xm-1>，Yn-1=<y1, y2, …, yn-1>，Zk-1=<z1, z2, …, zk-1>。
用c[i,j]记录序列Xi和Yj的最长公共子序列的长度。其中Xi=<x1, x2, …, xi>，Yj=<y1, y2, …, yj>。
当i=0或j=0时，空序列是Xi和Yj的最长公共子序列，故c[i,j]=0。
*/

/*
function LCSLength(X[1..m], Y[1..n])
    C = array(0..m, 0..n)
    for i := 0..m
       C[i,0] = 0
    for j := 0..n
       C[0,j] = 0
    for i := 1..m
        for j := 1..n
            if X[i] = Y[j]
                C[i,j] := C[i-1,j-1] + 1
            else
                C[i,j] := max(C[i,j-1], C[i-1,j])
    return C[m,n]
    */
// Longest Common Subsequence - LCS
// DP solution
int LCS_DP(char* x, int xlen, char* y, int ylen){
	int max_len = 0;
	int dp[MAXLEN][MAXLEN] = {0};

	for (int i = 0; i < xlen; ++i)
		dp[i][0] = 0;
	for (int j = 0; j < ylen; ++j)
		dp[0][j] = 0;

	for (int i = 1; i < xlen; ++i)
		for (int j = 1; j < ylen; ++j){
			if (x[i] == y[j]){
				dp[i][j] = dp[i-1][j-1] + 1;
			}else{
				dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
			}
		}

	return dp[xlen][ylen];
}

// rolling array
// the main codes pieces
    for(i = 1; i <= xlen; ++i)
    {
        k = i & 1;
        for(j = 1; j <= ylen; ++j)
        {
            if(X[i-1] == Y[j-1])
            {
                dp[k][j] = dp[k^1][j-1] + 1;
            }else if(dp[k][j-1] > dp[k^1][j])
            {
                dp[k][j] = dp[k][j-1];
            }else
            {
                dp[k][j] = dp[k^1][j];
            }
        }
    }
    
// another solution...    
function backtrack(C[0..m,0..n], X[1..m], Y[1..n], i, j)
    if i = 0 or j = 0
        return ""
    else if  X[i] = Y[j]
        return backtrack(C, X, Y, i-1, j-1) + X[i]
    else
        if C[i,j-1] > C[i-1,j]
            return backtrack(C, X, Y, i, j-1)
        else
            return backtrack(C, X, Y, i-1, j)
