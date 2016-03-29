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

bool isInterleaving_v2(string s1, string s2, string s3){
    int len1=s1.size(), len2=s2.size(), len3=s3.size();        
    if(len1+len2 != len3) return false;

    //switch to save space later on.
    if(len2>len1)  {string tmp=s2; s2=s1; s1=tmp;}

    vector<bool> isPrefix(s2.size()+1, false);
    isPrefix[0]=true;

    for(int i=1; i<=s2.size(); i++) 
		isPrefix[i] = s2.substr(0, i) == s3.substr(0, i);

    for(int i=1; i<=s1.size(); i++){
        isPrefix[0] = s1.substr(0, i)==s3.substr(0,i);
        for(int j=1; j<=s2.size(); j++)
            isPrefix[j]= (isPrefix[j-1]&&s2[j-1]==s3[i+j-1] || isPrefix[j]&&s1[i-1]==s3[i+j-1]);
    }
    return isPrefix.back();
}

/*
If the two strings are 'ab' and 'cd', the output I wish to get is:

['abcd', 'acbd', 'acdb', 'cabd', 'cadb', 'cdab']
*/

void printIlsRecur (char *str1, char *str2, char *iStr, int m, 
                    int n, int i)
{
    // Base case: If all characters of str1 and str2 have been 
    // included in output string, then print the output string
    if (m==0 && n==0)
        printf("%s\n", iStr) ;
 
    // If some characters of str1 are left to be included, then
    // include the  first character from the remaining characters
    // and recur for rest
    if (m != 0)
    {
        iStr[i] = str1[0];
        printIlsRecur (str1 + 1, str2, iStr, m-1, n, i+1);
    }
 
    // If some characters of str2 are left to be included, then
    // include the  first character from the remaining characters 
    // and recur for rest
    if (n != 0)
    {
        iStr[i] = str2[0];
        printIlsRecur(str1, str2+1, iStr, m, n-1, i+1);
    }
}
 
// Allocates memory for output string and uses printIlsRecur()
// for printing all interleavings
void printIls (char *str1, char *str2, int m, int n)
{
   // allocate memory for the output string
   char *iStr= (char*)malloc((m+n+1)*sizeof(char));
 
   // Set the terminator for the output string
   iStr[m+n] = '\0';
 
   // print all interleavings using printIlsRecur()
   printIlsRecur (str1, str2, iStr, m, n, 0);
 
   // free memory to avoid memory leak
   free(iStr); 
}

// python version
def interleave(s, t, res, i, j, lis):
    if i == len(s) and j == len(t):
        lis.append(res)
        return
    if i < len(s):
        interleave(s, t, res + s[i], i + 1, j, lis)
    if j < len(t):
        interleave(s, t, res + t[j], i, j + 1, lis)
