//finding all increasing subsequences in given sequence.

// DP
/*
for i = 1 to n do
    dp[i] = 1
    for j = 1 to i - 1 do
        if input[j] < input[i] then
            dp[i] = dp[i] + dp[j] // we can just append input[i] to every subsequence ending with j
*/
