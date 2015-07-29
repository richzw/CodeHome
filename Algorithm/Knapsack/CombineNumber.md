Q: **What is an efficient way to count the number of non contiguous subsequences of a given array of integers divisible by n?**

Sample Input

  A = {1,2,3,2}

  n = 6

Output: 3, because 12, 12, 132 are divisible by 6

--------------------------------------------------------------

**[0-1 knapsack]**

We will use an array `dp[idx][m]` where `idx` is the length of the array considered so far and `m` is the modulo of the sub-sequence generated so far by `n`. 
`dp[idx][m]` signifies count of sub-sequences considering elements `array[1..idx]` with modulo `m`. So, the state for this problem is `(idx,m)`. 
So, the final answer will be given by considering whole array and having modulus by `n = 0`. 

We will solve it by memoization. The code is given below.

```c
int len, ar[MAXLEN], dp[MAXLEN][MAXN];
int fun(int idx, int m)
{
    if(idx == len)                          // One sub-sequence completed
        return (m == 0);                    // return 1 only if modulus by n is 0
    if(dp[idx][m] != -1)
        return dp[idx][m];
    int ans = fun(idx+1, m);                // skip this element in current sub-sequence
    ans += fun(idx+1, (m*10 + ar[idx])%n);    // Include this element. Find the new modulo by 'n' and pass it recursively
    return dp[idx][m] = ans;
}
int main()
{
    // input len , n , array
    memset(dp, -1, sizeof(dp));
    printf("%d\n", fun(0, 0));            // initially we begin by considering array of length 1 i.e. up to index 0
    return 0;
}
```
