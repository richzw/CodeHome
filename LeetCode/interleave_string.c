/*
3个字符串a，b，c。判断c是否是a和b的interleave，也就是c中应该有a，b中所有字 符，并且c中字符顺序和a，b中一样。比如，
	1. a = "ef" b = "gh" c = "egfh" return true；
	2. a = "ef" b = "gh" c = "ehgf" return false。
*/

/*
分析这个题目中，并没有说明a和b中是否有相同的字符，这个直接影响了最终的解法。所以，大家在面试的过程中，要和面试官进行交互，
弄清楚之后再动手。我们这里对于是否有相同的字符都给予分析。希望对大家有所帮助。

a和b没有相同字符的情况
*/

bool isInterleaved(char* a, char* b, char* c){
  while (*c != 0){
    if (*a == *c)
      a++;
    else if(*b == *c)
      b++;
    else
      return false;
    c++;
  }
  
  if (*a || *b)
    return false;
    
  return true;
}

/*
a和b有相同字符的情况上面的算法，
不能够处理a和b中有相同字符的情况，例如a="XXY"，b="XXZ"，c="XXZXXY"。如果要处理，有相同字符的情况也是比较直接的。
有相同的出现，如果都匹配了c中的字符，则两种匹配分别都考虑，只要有一个返回true，整个算法就返回true。
*/
bool isInterleaved(char* a, char* b, char* c){
	if (!(*a || *b || *c))
		return true;
	if (*c == '\0')
		return false;
		
	return ((*c == *a && isInterleaved(a+1, b, c+1))
		||(*c == *b && isInterleaved(a, b+1, c+1)));
}
/*
下面介绍一个动态规划的解法。一个问题能够用动态规划来解的一个前提是：要有重复的子 问题。这样把子问题的解存储起来，
后面重复利用才可以提高算法的效率。这个问题有子问题么？考虑一个极端的例 子:a="XXX"，b="XXX"，c="XXXXXX"。子问题，
显然存在。再不然，画出递归树，就很明了了。
*/

bool isInterleaved(char* a, char* b, char* c)
{
	int M = strlen(a), N = strlen(b);
	bool I[M+1][N+1];
	memset(I, 0, sizeof(I));

	if ((M+N) != strlen(c))
		return false;

	for (int i = 0; i < M + 1; ++i)
		for (int j = 0; j < N + 1; ++j){
			if (i == 0 && j == 0)
				I[i][j] = true;
			// a is null
			else if (i == 0 && b[j-1] == c[j-1])
				I[i][j] = I[i][j-1];
			// b is null
			else if (j == 0 && a[i-1] == c[i-1])
				I[i][j] = I[i-1][j];
			// match a
			else if (a[i-1] == c[i+j-1] && b[j-1] != c[i+j-1])
				I[i][j] = I[i-1][j];
			// match b
			else if (a[i-1] != c[i+j-1] && b[j-1] == c[i+j-1])
				I[i][j] = I[i][j-1];
			//  match a and b at the same time
			else if (a[i-1] == c[i+j-1] && b[j-1] == c[i+j-1])
				I[i][j] = (I[i][j-1] || I[i-1][j]);
		}

	return I[M][N];
}
