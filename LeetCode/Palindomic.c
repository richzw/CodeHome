// solution1: O(n^2) time, O(n^2) space
 string findPalindomic(string strs){
     bool status_arr[100][100] = {false};
     int arr_len = strs.length();
     int max_len = 1;
     int begin_index = 0;

     for (int index = 0; index < arr_len; ++index){
         status_arr[index][index] = true;
     }

     for (int index = 0; index < arr_len-1; ++index){
         if (strs[index] == strs[index + 1]){
             status_arr[index][index+1] = true;
             begin_index = index;
             max_len = 2;
         }
     }

     for (int k = 3; k < arr_len; ++k){
         for (int j = 0; j < arr_len-k+1; ++j){
             int i = j + k - 1;
             if (strs[j] == sts[i] && status_arr[j+1][i-1]){
                 status_arr[j][i] = true;
                 begin_index = j;
                 max_len = k;
             }
         }
     }

     return strs.substr(begin_index, max_len);
 }


// solution2: O(n^2) time

string expandAroundCenter(string s, int c1, int c2) {
  int l = c1, r = c2;
  int n = s.length();
  while (l >= 0 && r <= n-1 && s[l] == s[r]) {
    l--;
    r++;
  }
  return s.substr(l+1, r-l-1);
}
 
string longestPalindromeSimple(string s) {
  int n = s.length();
  if (n == 0) return "";
  string longest = s.substr(0, 1);  // a single char itself is a palindrome
  for (int i = 0; i < n-1; i++) {
    string p1 = expandAroundCenter(s, i, i);  // for case 'aba'
    if (p1.length() > longest.length())
      longest = p1;
 
    string p2 = expandAroundCenter(s, i, i+1); // for case 'abba'
    if (p2.length() > longest.length())
      longest = p2;
  }
  return longest;
}

// DP
void isPalin(char* str)
{
	int len = strlen(str);
	bool p[len][len] = {false};

	// all strings which length is 1 is palin
	for (int i = 0; i < len; ++i)
		p[i][i] = true;

	for (int L = 2; L <= len; ++L)
		for (int i = 0; i < len - L +1; ++i){
			j = i + len -1; // the end of palin string
			if (L == 2)
				p[i][j] = (str[i] == str[j]);
			else
				p[i][j] = (str[i] == str[j]) && p[i+1][j-1];
		}
}


// solution3: Manacher algorithm
// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
string preProcess(string s) {
  int n = s.length();
  if (n == 0) return "^$";
  string ret = "^";
  for (int i = 0; i < n; i++)
    ret += "#" + s.substr(i, 1);
 
  ret += "#$";
  return ret;
}
 
string longestPalindrome(string s) {
  string T = preProcess(s);
  int n = T.length();
  int *P = new int[n];
  int C = 0, R = 0;
  for (int i = 1; i < n-1; i++) {
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
      P[i]++;
 
    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }
 
  // Find the maximum element in P.
  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n-1; i++) {
    if (P[i] > maxLen) {
      maxLen = P[i];
      centerIndex = i;
    }
  }
  delete[] P;
  
  return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}
