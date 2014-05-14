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
	int sum = 0;

	for (int idx = 0; idx < len; ++idx){
		sum += arr[idx];
	}

	return isSubsetSum(arr, len, sum/2);
}
