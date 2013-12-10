/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2 
(each operation is counted as 1 step). You have the following 3 operations permitted on a word:
a) Insert a character
b) Delete a character
c) Replace a character

Thoughts:
First, we explain the recursive structure here. Denote ed(s_{1}, s_{2}) as the edit distance between s_{1} and s_{2}. 
For base case, we have:
ed('', '') = 0
ed('', s) = ed(s, '') = \|s\|
Then, for the recursive step, we have:
ed(s_{1}+ch1, s_{2}+ch2) = ed(s_{1}, s_{2}) if ch1 == ch2 
since we don’t need to anything from s_{1},s_{2} to s_{1}+ch1, s_{2}+ch2.
ed(s_{1}+ch1, s_{2}+ch2) = \min(1 + ed(s_{1}, s_{2}), 1 + ed(s_{1}+ch1, s_{2}), 1 + ed(s_{1}, s_{2}+ch2))
if ch1 != ch2. 
Here we compare three options:
Replace ch1 with ch2, hence 1 + ed(s_{1}, s_{2}).
Insert ch2 into s_{2}, hence 1 + ed(s_{1}+ch1, s_{2}).
Delete ch1 from s_{1}, hence 1 + ed(s_{1}, s_{2}+ch2).
*/
//DP version
int get_min_edit_distance(string word1, string word2){
	int len1 = word1.length();
	int len2 = word2.length();

	vector<vector<int> > vec(len1+1);
	for (int idx = 0; idx < len1+1; ++idx){
		vec[idx].resize(len2+1);
	}

	vec[0][0] = 0;
	for (int idx = 1; idx < len1+1; ++idx)
		vec[idx][0] = idx;
	for (int idx = 1; idx < len2+1; ++idx)
		vec[0][idx] = idx;

	for (int i = 1; i < len1+1; ++i){
		for (int j = 1; j < len2+1; ++j){
			if (word1[i-1] == word2[j-1])
				vec[i][j] = vec[i-1][j-1];
			else{
				vec[i][j] = min(min(vec[i-1][j], vec[i][j-1]), vec[i-1][j-1]) + 1;
			}
		}
	}

	return vec[len1][len2];
}
