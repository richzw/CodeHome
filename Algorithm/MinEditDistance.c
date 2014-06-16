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

//recursive version
int edit_distance_helper(string w1, int w1Idx, string w2, int w2Idx, unordered_map<string, int>& map){
	string key = to_string((long long)w1Idx) + "," + to_string((long long)w2Idx);
	unordered_map<string, int>::iterator itor; 
	if ((itor = map.find(key)) != map.end()){
		return itor->second;
	}

	int edit_dis = 0;
	if (w1Idx == w1.length()-1 && w2Idx < w2.length()){
		return w2.length() - w2Idx;
	}else if (w2Idx == w2.length()-1 && w1Idx < w1.length()){
		return w1.length() - w1Idx;
	}else {
		if (w1[w1Idx] == w2[w2Idx]){
			edit_dis = edit_distance_helper(w1, w1Idx+1, w2, w2Idx+1, map);
		}else{
			//insert
			int if_insert = edit_distance_helper(w1, w1Idx, w2, w2Idx+1, map) + 1;
			//replace
			int if_replace = edit_distance_helper(w1, w1Idx+1, w2, w2Idx+1, map) + 1;
			//delete
			int if_delete = edit_distance_helper(w1, w1Idx+1, w2, w2Idx, map) + 1;

			edit_dis = min(if_insert, min(if_replace, if_delete));
		}
	}
	map.insert(make_pair<string, int>(key, edit_dis));

	return edit_dis;
}

int min_edit_distance(string w1, string w2){
	unordered_map<string, int> hash_map;
	
	return edit_distance_helper(w1, 0, w2, 0, hash_map);
}

/*
Following the same method, the edit distance from "CHIAR" to "CHAIR" is 2:
    CHIAR → CHAR (delete 'I')
    CHAR → CHAIR (insert 'I')
I would like to count this as "1 edit", since I only exchange two adjacent letters.
*/
if s[i] = t[j] then 
  d[i, j] := d[i-1, j-1]
else if i > 0 and j > 0 and s[i] = t[j - 1] and s[i - 1] = t[j] then
  d[i, j] := minimum
             (
               d[i-2, j-2] + 1 // transpose
               d[i-1, j] + 1,  // deletion
               d[i, j-1] + 1,  // insertion
               d[i-1, j-1] + 1 // substitution
             )
else
  d[i, j] := minimum
             (
               d[i-1, j] + 1,  // deletion
               d[i, j-1] + 1,  // insertion
               d[i-1, j-1] + 1 // substitution
             )
