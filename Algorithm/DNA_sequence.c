/*
给定一系列代表疾病的DNA序列，同时已知一条DNA序列，计算改变最少的DNA序列来使这个DNA序列不包含疾病的DNA序列。例如：​
AAA​
AAG​
上面代表疾病的DNA序列。​
AAAG为已知的正常的DNA序列。​
输出：1。因为修改第三个字符即可。​
分析​
这是一个多模式串匹配的问题，不同的是这个题中最后要求输入串与所有的模式串都不匹配。比较容易想到的是用AC自动机，
如果有匹配结果则需要对输入串进行修改，这个过程需要不断的回溯，负责度达到指数级。​
通过分析可以发现这个题目具有最有子结构：dp[i][j]=min(dp[i][j], dp[i-1][nNext] + dna[i-1]!=k)，
dp[i][j]的意思是长度为i的文本串需要改变dp[i][j]个序列顺利到达状态j，nNext是从状态j可以转移到的非匹配成功的状态，
k代表当前边的权。最后在min(dp[len][j])即为所求。

*/
#define MAX 20
typedef struct Tries{
	bool danger;
	bool flag;	
	int next[MAX];
}Tries;
int find_dna_seq(char dna[]){
	int dp[MAX][MAX] = {0};
	int nP = 10; //tmp value
	int code[MAX];
	Tries* trie = new Tries[MAX];

	int len = strlen(dna);
	for (int i = 0; i <= len; ++i)
		for (int j = 0; j < nP; ++j)
			dp[i][j] = -1;
	
	int i, j, k;
	dp[0][0] = 0;
	for (i = 1; i <= len; ++i){
		for (j = 0; j < nP; ++j){
			if (trie[j].danger) continue;
			if (dp[i-1][j] == -1) continue;
			for (k = 0; k < 4; ++k){
				int nNext = trie[j].next[k];
				if (trie[nNext].danger)
					continue;
				int temp = dp[i-1][j] + (k != code[dna[i-1]]);
				dp[i][nNext] = min(dp[i][nNext], temp);
			}
		}
	}

	int result = -1;
	for (i = 0; i < nP; ++i){
		if (!trie[i].flag && dp[len][i] != -1){
			result = result == -1? dp[len][i]:min(result, dp[len][i]);
		}
	}

	return result;
}
