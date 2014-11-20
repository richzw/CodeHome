/*
Q:给定字符串，可以通过插入字符，使其变为回文。求最少插入字符的数量。例如：​
	1. ab最少插入1个字符，变为*b*ab​
	2. aa最少插入0个字符​
	3. abcd最少插入3个字符，*dcb*abcd​

分析这个题目的分析思路，和前面两期是非常相似的：给出递归的解法，发现重复的子问题，改进为动态规划的解法，
这是一个分析的过程，待同学们比较熟悉时候，可以直接给出动态规划的解决方案，就很好了。​
这个题目，递归该如何解呢？给定一个字符串str，长度为n，怎么插入最少的字符，是的字符串变为回文呢？
插入最少的字符，就是要尽量利用原来的字符，在原字符串str中，尽量利用更多能够匹配的字符。
怎么对这个问题进行分解呢？考虑str字符串整体：​
	1. 如果str[0]==str[n-1]，则问题转变为求str[1,n-2]，插入最少字符，得到回文​
	2. 如果str[0]!=str[n-1]，则需要插入一个字符要么和str[0]相同，要么和str[n-1]相同，​
		1. 如果和str[0]，则转变为str[1,n-1]，插入最少字符，得到回文​
		2. 如果和str[n-1]，则转变为str[0,n-2]，插入最少字符，得到回文​
上面的第2种情况中，需要取两个值最小值。则完成了问题的分解，并且，基本情况也分析完全，则有递归式为：​
fmi(str, l, h) = (str[l] == str[h]) ? fmi(str, l+1, h-1) : (min(fmi(str, i+1, h), fmi(str,l, h-1))+1)
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
