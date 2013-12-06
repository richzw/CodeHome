/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
Given:
s1 = "aabcc", s2 = "dbbca",
When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/
bool isInterleavingRecv(string s1, string s2, string s3, int i, int j, int k){
	if (i >= s1.length() && j >= s2.length() && k >= s3.length())
		return true;
	
	bool ret = false;
	if (i == s1.length())
		return s3.substr(k).compare(s2.substr(j));
	if (j == s2.length())
		return s3.substr(k).compare(s1.substr(i));

	if (s1[i] == s3[k] && s2[j] != s3[k]){
		ret = isInterleavingRecv(s1, s2, s3, i+1, j, k+1);
	}else if (s1[i] != s3[k] && s2[j] == s3[k]){
		ret = isInterleavingRecv(s1, s2, s3, i, j+1, k+1);
	}else if (s1[i] == s3[k] && s2[j] == s3[k]){
		ret = isInterleavingRecv(s1, s2, s3, i+1, j, k+1);
		if (!ret)
			ret = isInterleavingRecv(s1, s2, s3, i, j+1, k+1);
	}

	return ret;
}

bool isInterleaving(string s1, string s2, string s3){
	if (s1.length() + s2.length() != s3.length())
		return false;
	else
		return isInterleavingRecv(s1, s2, s3, 0, 0, 0);
}

bool isInterleaving_v1(string s1, string s2, string s3){
	int len1 = s1.length();
	int len2 = s2.length();
	int len3 = s3.length();

	vector<vector<bool> > vec(len1+1);
	for (int idx = 0; idx < len1+1; ++idx){
		vec[idx].resize(len2+1);
	}

	vec[0][0] = true;
	for (int idx = 0; idx < len1; ++idx){
		if (s1[idx] == s3[idx])
			vec[idx+1][0] = true;
		else
			break;
	}

	for (int idx = 0; idx < len2; ++idx){
		if (s2[idx] == s3[idx])
			vec[0][idx+1] = true;
		else 
			break;
	}

	for (int i = 1; i < len1+1; ++i){
		for (int j = 1; j < len2+1; ++j){
			vec[i][j] = (vec[i][j-1] && s3[i+j-1] == s2[j-1]) || (vec[i-1][j] && s3[i+j-1] == s1[i-1]);
		}
	}

	return vec[len1][len2];
}
