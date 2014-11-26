//Q Number of Increasing Subsequences of length k


dp[i, j] = number of increasing subsequences of length j that end at i
num[i] = how many subsequences that end with i (element, not index this time) 
         have a certain length

An easy solution is in O(n^2 * k):

for i = 1 to n do
  dp[i, 1] = 1

for i = 1 to n do
  for j = 1 to i - 1 do
    if array[i] > array[j]
      for p = 2 to k do
        dp[i, p] += dp[j, p - 1]
The answer is dp[1, k] + dp[2, k] + ... + dp[n, k]

More efficiency solution is here

for i = 1 to n do   dp[i, 1] = 1

for p = 2 to k do // for each length this time   num = {0}
  for i = 2 to n do
    // note: dp[1, p > 1] = 0 

    // how many that end with the previous element
    // have length p - 1
    num[ array[i - 1] ] += dp[i - 1, p - 1]   *1*   

    // append the current element to all those smaller than it
    // that end an increasing subsequence of length p - 1,
    // creating an increasing subsequence of length p
    for j = 1 to array[i] - 1 do   *2*       
      dp[i, p] += num[j]

This has complexity O(n * k * S), but we can reduce it to O(n * k  * log S) quite easily. 
You can optimize *1* and *2* by using segment trees or binary indexed trees. 
These will be used to efficiently process the following operations on the num array:
	Given (x, v) add v to num[x] (relevant for *1*);
	Given x, find the sum num[1] + num[2] + ... + num[x] (relevant for *2*).



//http://stackoverflow.com/questions/16402854/number-of-increasing-subsequences-of-length-k
