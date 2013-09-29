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
