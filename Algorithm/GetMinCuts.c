/*
给定一个String str, 切n刀，使得每个substr都是回文的，求最小的n， 然后保存切法，最后计算时间复杂度

例如： abbab 切一刀 变成 abba, b
-------------------------------------------------------------------------------------
这题一般人一看就是DP，DP公式也很容易推出，算是一道简单的DP。
dp(i)=min(1+dp(j+1) if s(i,j) is palindrome, j from i until n)
从以上的分析时间复杂度为O(n^3), 主要是因为检查回文也需要O(n)的时间。因此这题有意思的一点就是如何降低时间复杂度到O(n^2)？
其实这题是两个DP混杂在了一起，这也是这道题最有意思的地方。另外一个DP就是跟检查回文有关了，公式如下
dp(i)(j)=true if s(i)==s(j) && dp(i+1)(j-1)
也就是说，你要检查一个回文只需要知道头尾的字符相等，并且中间的字串已经成为了回文即可。O(1)复杂度。

    def solve(s:String):Int={
        val n=s.length
        val pos=Array.ofDim[Boolean](n,n)
        val dp=Array.tabulate(n+1)(i=>n-i)
        
        for(i <- n-1 to 0 by -1; j <- i until n if(s(i)==s(j) && (j-i<2 || pos(i+1)(j-1)))){
            pos(i)(j)=true
            dp(i)=math.min(dp(i), 1+dp(j+1))
        }
        dp(0)-1
    }
*/
int getMinCuts(string str){
	int len = str.length();
	char* dp = new char[len];
	char** pos = new char*[len];
	for (int i = 0; i < len; ++i)
		pos[i] = new char[len];

	for (int i = 0; i < len; ++i)
		dp[i] = 0;
	for (int i = 0; i < len; ++i)
		for (int j = 0; j < len; ++j)
			pos[i][j] = false;

	for (int i = len-1; i >= 0; --i)
		for (int j = 0; j < len; ++j){
			if (str[i] == str[j] && (j - i < 2 || pos[i+1][j-1])){
				pos[i][j] = true;
				dp[i] = min(dp[i], 1+dp[j+1]);
			}
		}

	return dp[0];
}
