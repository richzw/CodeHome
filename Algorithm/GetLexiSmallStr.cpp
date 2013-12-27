/*
Given an array of words, get the lexicographically smallest string?

If no word appears to be a prefix of any other words, 
then the simple sort + concatenate must yield the smallest dictionary order string.
*/

/*
We have found the smallest-ordered word such that s1+x < x+s1. Therefore, 
it is impossible to swap the words to yield a smaller dictionary order.
For a case with more words, then this order relation holds: s1+x < x+s1, and x+y < y+x. 
As swapping at any point could not possibly yield a smaller dictionary order, therefore s1+x+y must yield the smallest dictionary order.
*/
bool str_cmp(string& s1, string& s2){
	return s1+s2 < s2+s1;
}

string get_small_dictionary_string(string strArr[], int len){
	string small_str = "";

	sort(strArr, strArr+len, str_cmp);

	for (int idx = 0; idx < len; ++idx)
		small_str += strArr[idx];

	return small_str;
}
