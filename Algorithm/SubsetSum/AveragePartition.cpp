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
