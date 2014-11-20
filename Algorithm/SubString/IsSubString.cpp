/*
给定两个字符串A和B，判断A中是否包含由B中字符重新排列成的新字符串。例如：A=abcdef, B=ba，结果应该返回true。
因为ba的排列ab，是A的子串。

我们假设A字符串的长度为m，B字符串的长度为n。首先，如果B的长度大于A了，则肯定返回的是false。
所以，我们下面的讨论都是m>=n的情况。
最直接的，我们可以计算出B的所有排列字符串，然后逐个去A中匹配。B的所有排列字符串有n!个，每一个匹配，复杂度较高。
那么如何改进呢？是否可以减少匹配的次数呢？我们首先对B进行排序，采用快排，时间复杂度O(nlogn)，得到D。
然后在A中，从头开始，长度为 n的子串进C行排序，然后判断与C与D是否相同。在A中，一共有m-n+1个长度为n的子串，
每一个子串进行排序，时间复杂度为O(nlogn)，总的时 间复杂度为O((m-n+1)nlogn),O(mnlogn)。
但其实，在A中，只有第一个C的排序时O(nlogn)的，其他的都是去掉第一个字符， 然后插入下一个字符，排序时间复杂度为O(n)，
这样整体的时间复杂度为O(mn)。下面举个例子：
设定A=fedcba, B=ab，则m=6，n=2
        1. 排序B，D=ab
        2. 在A中，第一个长度为2的子串C=fe，排序之后为ef，与D不匹配，则从C中删除第一个字符f，加入下一个字符c，
        此时C=ec。再重复排序的过程。直到A遍历完毕。
明显第一个C需要快排，其他的只需要插入即可。
还有其他的方法，可以用hashmap存储B中的字符，和A中的每一个长度为n的字串进行判断是否匹配。
*/
bool is_sub_string_ofA(string a, string b)
{
	int len_a = a.length();
	int len_b = b.length();
	if (len_a < len_b)
		return false;

	sort(b.begin(), b.end());

	string tmp = a.substr(0, len_b);
	a.erase(0, len_b);
	while (a.length() > 0){
		sort(tmp.begin(), tmp.end()); // insert sort is better
		if (tmp == b)
			return true;
		tmp.erase(0, 1); //delete the first char from test string
		tmp.push_back(a[0]);
		a.erase(0, 1);   // delete the first char from the original string
	}

	return false;
}
