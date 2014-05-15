/*
 Partition problem is to determine whether a given set can be partitioned into two subsets such that the sum of elements in both subsets is same.
Examples
arr[] = {1, 5, 11, 5}
Output: true 
The array can be partitioned as {1, 5, 5} and {11}

arr[] = {1, 5, 3}
Output: false 
The array cannot be partitioned into equal sum sets.
*/
/*
Let isSubsetSum(arr, n, sum/2) be the function that returns true if 
there is a subset of arr[0..n-1] with sum equal to sum/2

The isSubsetSum problem can be divided into two subproblems
 a) isSubsetSum() without considering last element 
    (reducing n to n-1)
 b) isSubsetSum considering the last element 
    (reducing sum/2 by arr[n-1] and n to n-1)
If any of the above the above subproblems return true, then return true. 
isSubsetSum (arr, n, sum/2) = isSubsetSum (arr, n-1, sum/2) ||
                              isSubsetSum (arr, n-1, sum/2 - arr[n-1])
*/
bool isSubsetSum(int arr[], int idx, int sum){
	if (sum == 0)
		return true;

	if (idx == 0 && sum != 0)
		return false;

	if (arr[idx] > sum)
		return isSubsetSum(arr, idx-1, sum);

	return isSubsetSum(arr, idx-1, sum) || isSubsetSum(arr, idx-1, sum-arr[idx-1]);
}

bool isPartitionArray(int arr[], int len){
	if (arr == NULL || len <= 1)
		return false;

	int sum = 0;

	for (int idx = 0; idx < len; ++idx){
		sum += arr[idx];
	}

	if (sum%2 != 0)
		return false;
		
	return isSubsetSum(arr, len, sum/2);
}

/*
DP:
part[i][j] = true if a subset of {arr[0], arr[1], ..arr[j-1]} has sum 
             equal to i, otherwise false 
*/
bool isPartitionArr_dp(int arr[], int len){
	if (arr == NULL || len <= 1)
		return false;
	int sum = 0;

	for (int idx = 0; idx < len; ++idx){
		sum += arr[idx];
	}

	if (sum%2 != 0)
		return false;

	//int dp[sum/2 + 1][len+1]; // dynamic program array
	// Fixme: the length should be sum/2+1 and len+1
	bool** dp = new bool*[sum/2+1];
	for (int i = 0; i < sum/2+1; ++i)
		dp[i] = new bool[len+1];

	memset(dp, false, sizeof(int)*len*sum/2);

	// initialize the dp array
	for (int i = 0; i <= sum/2; ++i){
		dp[i][0] = false;
	}
	for (int j = 0; j <= len; ++j){
		dp[0][j] = true;
	}

	// Fill up the dp array in bottom-up mode
	for (int i = 1; i <= sum/2; ++i){
		for (int j = 1; j <= len; ++j){
			dp[i][j] = dp[i][j-1];
			if (i > arr[j])
				dp[i][j] = dp[i][j] || dp[i-arr[j]][j-1];
		}
	}

	return dp[sum/2][len];
}
