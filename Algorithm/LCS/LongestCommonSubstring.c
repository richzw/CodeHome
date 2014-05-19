//

// LCS
// solution 1: brute force
int common_length(char* p, char* q){
	int len = 0; 
	while (*p && *q && *p++ == *q++)
		++len;
	return len;
}

int LCS_BF(char* x, int xlen, char* y, int ylen){
	int max_len = 0;

	for (int i = 0; i < xlen; ++i)
		for (int j = 0; j < ylen; ++j){
			int len = common_length(&x[i], &y[j]);
			if (len > max_len)
				max_len = len;
		}

	return max_len;
}

/*
Solution2: DP
First find the longest common suffix for all pairs of prefixes of the strings. The longest common suffix is
   LCSuff(S(1..p), T(1..q)) = LCSuff(S(1..p-1), T(1..q-1)) + 1 if S[p] = T[q] else 0.

For the example strings "ABAB" and "BABA":
  	A	B	A	B
	0	0	0	0	0
B	0	0	1	0	1
A	0	1	0	2	0
B	0	0	2	0	3
A	0	1	0	3	0
The maximal of these longest common suffixes of possible prefixes must be the longest common substrings of S and T. 
These are shown on diagonals, in red, in the table. For this example, the longest common substrings are "BAB" and "ABA".

LCSubstr(S,T) = max(LCSuff(S(1..i), T(1..j))) (1<i<m, 1<j<n)
*/
//solution 2: DP
#define MAXLEN 100
int LCS_DP(char* x, int xlen, char* y, int ylen){
	int max_len = 0;
	int dp[MAXLEN][MAXLEN] = {0};

	for (int i = 0; i < xlen; ++i)
		for (int j = 0; j < ylen; ++j){
			if (x[i] == y[j]){
				if (i == 0 || j == 0){
					dp[i][j] = 1;
				}else{
					dp[i][j] = dp[i-1][j-1] + 1;
				}

				if (dp[i][j] > max_len){
					max_len = dp[i][j];
				}
			} 
		}
	return max_len
}

// DP improvement - rolling array
// dp[i][j] only related with dp[i-1][j-1]
int LCS_DP_improve(char* x, int xlen, char* y, int ylen){
	int max_len = 0;
	int dp[2][MAXLEN] = {0};

	for (int i = 0; i < xlen; ++i){
		int k = i & 1;
		for (int j = 0; j < ylen; ++j){
			if (x[i] == y[j]){
				if (i == 0 || j == 0){
					dp[k][j] = 1;
				}else{
					dp[k][j] = dp[k^1][j-1] + 1;
				}

				if (dp[i][j] > max_len){
					max_len = dp[i][j];
				}
			} 
		}
	}
	return max_len
}


/*
Solution1: suffix tree
Building the suffix tree takes O(N), the size of alphabet is constant, find the string costs O(n+m)
*/
// solution 3: suffix array
char * suff[100];
 
int pstrcmp(const void *p, const void *q)
{
    return strcmp(*(char**)p,*(char**)q);
}
 
int comlen_suff(char * p, char * q)
{
    int len = 0;
    while(*p && *q && *p++ == *q++)
    {
        ++len;
        if(*p == '#' || *q == '#')
        {
            return len;
        }
    }
    int count = 0;
    while(*p)
    {
        if(*p++ == '#')
        {
            ++count;
            break;
        }
    }
    while(*q)
    {
        if(*q++ == '#')
        {
            ++count;
            break;
        }
    }
    if(count == 1)
        return len;
    return 0;
}
 
void LCS_suffix(char * X, int xlen, char * Y, int ylen)
{
    int suf_index, maxlen, maxindex = 0;
 
    int len_suff = xlen + ylen + 1;
    char * arr = new char [len_suff + 1];  // connect x with y
    strcpy(arr,X);
    arr[xlen] = '#';
    strcpy(arr + xlen + 1, Y);
 
    for(int i = 0; i < len_suff; ++i) // initialize the array
    {
        suff[i] = & arr[i];
    }
 
    qsort(suff, len_suff, sizeof(char *), pstrcmp); // sort the array
 
    for(int i = 0; i < len_suff-1; ++i)
    {
        int len = comlen_suff(suff[i],suff[i+1]);
        if(len > maxlen)
        {
            maxlen = len;
            suf_index = i;
        }
    }
}

