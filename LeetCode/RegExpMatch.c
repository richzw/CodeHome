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
