// Get all substrings with length no more than 3 from one given string,
// all those substrings are sorted by the number of occurrences and the same number of occurences sorted by lexicographical order.
/* for example: s="aabcab" 
output:
a 3 
ab 2 
b 2 
aa 1 
aab 1 
abc 1 
bc 1 
bca 1 
c 1 
ca 1 
cab 1 
*/
map<string, int> getSubStringsLessThan(const string s, int k){
	map<string, int> substr_map;
	int len = s.length();

	for (int i = 0; i < len; ++i){
		for (int j = 1; j <= k && j <= (len-i); ++j){
			string sub = s.substr(i, j);

			substr_map[sub]++;
		}
	}

	return substr_map;
}

bool pair_compare(pair<string, int> &a, pair<string, int> &b){
	if (a.second > b.second)
		return true;
	else if (a.second < b.second)
		return false;
	else 
		return a.first < b.first;
}


vector<pair<string, int>> generateStrLen3(const string s){
	map<string, int> ret = getSubStringsLessThan(s, 3);

	vector<pair<string, int>> vec_str(ret.size());
	transform(ret.begin(), ret.end(), back_inserter(vec_str), [](pair<string, int> v){ return v; });

	sort(vec_str.begin(), vec_str.end(), pair_compare);

	return vec_str;
}
