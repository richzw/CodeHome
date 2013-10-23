/*

*/

//fmi(str, l, h) = (str[l] == str[h]) ? fmi(str, l+1, h-1) : (min(fmi(str, i+1, h), fmi(str,l, h-1))+1)
int find_min_plalindrome_dp(char pla[], int len)
{
	int** ary = new int*[len];
	for (int i = 0; i < len; ++i)
		ary[i] = new int[len];

	memset(ary, 0, sizeof(int)*len*len);
	int low, high, gap;

	for (gap = 0; gap < len; ++gap)
		for (low = 1, high = gap; high < len; ++low, ++high)
		{
			ary[low][high] = (pla[low] == pla[high])?ary[low+1][high-1]:
								(min(ary[low+1][high], ary[low][high-1]) + 1);
		}

	return ary[0][len-1];
}
