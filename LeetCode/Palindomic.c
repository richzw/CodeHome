
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

// solution3: Manacher algorithm
