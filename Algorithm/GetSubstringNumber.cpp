/*
 给定两个字符串s和t(len(s)>len(t))，t可能是s的一个子序列。求所有s的子序列集合中，有多少个子序列等于t。
 例如s="abbbc"，t="abc"，结果为3，即在s的所有子序列集合中，有3个子序列为t。 
 分析： 对于这个题目，我们可以很直观的想到递归解法，如果当前t[i]==s[j]，则f[i,j] = f[i+1, j+1] + f[i, j+1]，
 否则f[i,j] = f[i, j+1]。但是用递归的方法会产生大量的重复计算，时间复杂度很高。如何能减少重复计算呢，相信大家都能想到动态规划。
 仔细推敲一下是否能得到一个动态规划的递推公式。当t[i]==s[j]时，我们可以用当前的s[j]来匹配t[i]，那么f[i,j]就依赖于f[i-1, j-1]，
 同时，我们也可以不用当前的s[j]来匹配t[i],那么f[i,j]依赖于f[i,j-1]，
 因此我们可以得到递推公式如下： if(t[i]==s[j]) f[i,j] = f[i-1][j-1] + f[i][j-1] else f[i,j] = f[i][j-1] 
 时间复杂度o(m*n)，m和n分别是字符串s和t的长度。
 与这种题目类似的还有编辑距离问题，某个字符串是否是另外两个字符串的interleaving问题，
*/
int get_sub_string_number(string str, string subStr){

}

int numSubSequence(string s, string t){
	if (s.size() == 0 || t.size() == 0)
		return 0;
	vector<vector<int> > vec(t.size() + 1);
	for (int i = 0; i <= t.size(); ++i){
		vec[i].resize(s.size() + 1);
		vec[i][0] = 0;
	}

	for (int j = 0; j <= s.size(); ++j)
		vec[0][j] = 1;

	for (int i = 0; i < t.size(); ++i)
		for (int j = 0; j < s.size(); ++j){
			if (t[i] == s[j])
				vec[i+1][j+1] = vec[i][j] + vec[i+1][j];
			else
				vec[i+1][j+1] = vec[i+1][j];
		}

	return vec[t.size()][s.size()];
}
