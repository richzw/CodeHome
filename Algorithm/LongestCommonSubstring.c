Solution1: suffix tree
Building the suffix tree takes O(N), the size of alphabet is constant, find the string costs O(n+m)

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
