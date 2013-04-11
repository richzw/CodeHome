/*
* Q: ‘.’ Matches any single character.
*    ‘*’ Matches zero or more of the preceding element.
* EX:
*   isMatch(“aa”,”a”) → false
	isMatch(“aa”,”aa”) → true
	isMatch(“aaa”,”aa”) → false
	isMatch(“aa”, “a*”) → true
	isMatch(“aa”, “.*”) → true
	isMatch(“ab”, “.*”) → true
	isMatch(“aab”, “c*a*b”) → true
*
*/
bool isMatch(const char* s, const char* p)
{
	if (*s == NULL && *p == NULL)
		return true;
	else if (*s == NULL || *p == NULL)
		return false;

	if (*p == '.' && *(p+1) != '*'){
		return isMatch(++s, ++p);
	}else if (*p == '.' && *(p+1) == '*'){
		return true;  // bug here, greed is not good!!!
	}else if (*p != '*' && *(p+1) == '*'){
		while (*s == *p) // bug herer, greed is not good!!!
			++s;
		p += 2; //skip the pre element and '*'
		return isMatch(s, p);
	}else {
		if (*s == *p)
			return isMatch(++s, ++p);
		else
			return false;
	} 
}

//To fix those bugs, some kind of backtracking mechanism such that when a matching fails
bool isMatch(const char *s, const char *p) {
  assert(s && p);
  if (*p == '\0') return *s == '\0';
 
  // next char is not '*': must match current character
  if (*(p+1) != '*') {
    assert(*p != '*');
    return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
  }
  // next char is '*'
  while ((*p == *s) || (*p == '.' && *s != '\0')) {
    if (isMatch(s, p+2)) return true;
    s++;
  }
  return isMatch(s, p+2);
}
