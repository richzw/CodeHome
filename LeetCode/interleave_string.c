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
