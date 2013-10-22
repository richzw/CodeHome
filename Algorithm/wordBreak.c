/*
Q:给定字符串，以及一个字典，判断字符串是否能够拆分为字段中的单词。例如，字段为{hello，world}，字符串为hellohelloworld，
则可以拆分为hello,hello,world，都是字典中的单词。
*/

/*
brute force
*/
bool dictionaryContains(vector<string> vec, string str)
{
	for (vector<string>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
	{
		if (*iter == str)
			return true;
	}
	return false;
}

bool word_break(vector<string> vec, string str)
{
	int len = str.length();
	if (len == 0)
		return true;
	for (int i = 0; i < len; ++i)
	{
		if (dictionaryContains(vec, str.substr(0, i)) 
			&& word_break(vec, str.substr(i, len - i)))
			return true;
	}
	return false;
}

/*
DP
*/
bool word_break_sub(vector<string> vec, string str, int* dp, int index, int len)
{
	if (index > len || index < 0)
		return false;
	if (index == len && dp[index] == true)
		return true;

	if (dp[index] == false && dictionaryContains(vec, str))
		dp[index] == true;

	return word_break_sub(vec, str.substr(0, index++), dp, 0, len)
		&& word_break_sub(vec, str.substr(index, len-index), dp, 0, len);
}

bool word_break_dp(vector<string> vec, string str)
{
	int len = vec.size();
	if (len == 0)
		return true;
	int* dp = new int[len];
	memset(dp, 0, sizeof(int));

	return word_break_sub(vec, str, dp, 0, len);
}
