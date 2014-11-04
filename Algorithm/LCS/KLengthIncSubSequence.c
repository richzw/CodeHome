//Q Number of Increasing Subsequences of length k

/*
dp[i, j] = same as before num[i] = how many subsequences that end with i (element, not index this time) 
         have a certain length

for i = 1 to n do   dp[i, 1] = 1

for p = 2 to k do // for each length this time   num = {0}

  for i = 2 to n do
    // note: dp[1, p > 1] = 0 

    // how many that end with the previous element
    // have length p - 1
    num[ array[i - 1] ] += dp[i - 1, p - 1] *1*   

    // append the current element to all those smaller than it
    // that end an increasing subsequence of length p - 1,
    // creating an increasing subsequence of length p
    for j = 1 to array[i] - 1 do *2*       
      dp[i, p] += num[j]
*/


//http://stackoverflow.com/questions/16402854/number-of-increasing-subsequences-of-length-k
