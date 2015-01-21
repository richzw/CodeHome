/*
To determine whether a given set can be partitioned into two subsets 
such that the sum of elements in both subsets is same
*/
bool AveragePartitionRec(vector<int> v, int idx, int sum){
	if((idx >= v.size()) && sum != 0)
		return false;
	if (sum == 0)
		return true;

	if (v[idx] > sum)
		return AveragePartitionRec(v, idx+1, sum);

	return AveragePartitionRec(v, idx+1, sum) &&
				AveragePartitionRec(v, idx+1, sum-v[idx]);
}

bool AveragePartitionByRecur(vector<int> v){
	int len = v.size();
	int sum = accumulate(v.begin(), v.end(), 0);
	
	if (sum%2 != 0) // odd number, can not be divided equally
		return false;
	
	return AveragePartitionRec(v, 0, sum/2);
}

// Dynamic programming
// part[i][j] = true if a subset of {arr[0], arr[1], ...arr[j-1]} has sum equal to i, otherwise false
bool AveragePartitionDP(vector<int> v){
	int n = v.size();
	int sum = accumulate(v.begin(), v.end(), 0);

	if (sum % 2 != 0)
		return false;

	vector<vector<bool> > dp(sum/2+1, vector<bool>(n+1));

	// initialize the dp array
	for (int idx = 0; idx < sum/2 + 1; ++idx)
		dp[idx][0] = false;
	for (int idx = 0; idx < n + 1; ++idx)
		dp[0][idx] = true;
	
	for (int i = 1; i < sum/2+1; ++i)
		for (int j = 1; j < n+1; ++j){
			dp[i][j] = dp[i][j-1];
			if (i >= v[j-1])
				dp[i][j] = dp[i][j]|| dp[i-v[j-1]][j-1];
		}

	return dp[sum/2][n];
}
