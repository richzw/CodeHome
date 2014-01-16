/*
You have to paint N boards of length {A0, A1, A2 … AN-1}. 
There are K painters available and you are also given how much time a painter takes to paint 1 unit of board.
You have to get this job done as soon as possible under the constraints that any painter will only paint continuous sections of board,
say board {2, 3, 4} or only board {1} or nothing but not board {2, 4, 5}.

means:
Given an array of non-negative integers A and a positive integer k, we want to:
Divide A into k or fewer partitions,
such that the maximum sum over all the partitions is minimized.
*/
/*
                 n                n-1
M[n, k] = min { max { M[j, k-1], ∑ Ai } }
                j=1               i=j
*/
int sum_paintboard(int arr[], int start, int stop){
	int totle = 0;
	for (int i = start; i <= stop; ++i)
		totle += arr[i];

	return totle;
}
int partition_paintboard(int arr[], int len, int k){
	if (k == 1)
		return sum_paintboard(arr, 0, len-1);
	if (len == 1)
		return arr[0];

	int best = INT_MAX;
	for (int i = 1; i < len; ++i)
		best = min(best, max(partition_paintboard(arr, i, k-1), sum_paintboard(arr, i, len-1)));

	return best;
}
