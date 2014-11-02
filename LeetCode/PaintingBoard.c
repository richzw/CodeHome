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

// more efficient ... DP method
const int _SIZE = 100;
int partition_dp(int arr[], int len, int k){
	int dp[_SIZE][_SIZE] = {0};
	int sum[_SIZE] = {0};

	for (int i = 1; i < len; ++i)
		sum[i] = sum[i-1] + arr[i-1];

	for (int i = 1; i <= len; ++i)
		dp[i][1] = sum[i];
	for (int j = 1; j <= k; ++j)
		dp[1][j] = arr[0];

	for (int i = 2; i <= k; ++i){
		for (int j = 2; j <= len; ++j){
			int best = INT_MAX;
			for (int p = 1; p <= j; ++p)
				best = min(best, max(dp[p][i-1], sum[j]-sum[p]));
			dp[j][i] = best;
		}
	}

	return dp[len][k];
}
// the best idea...
//The lowest possible value for costmax must be the maximum element in A (name this as lo).
//The highest possible value for costmax must be the entire sum of A, (name this as hi).
//As costmax increases, x decreases. The opposite also holds true.
//How do we use binary search to find the minimum of costmax while satisfying the condition x = k? The search space will be the range of [lo, hi].
//The complexity of this algorithm is O(N log ( ∑ Ai ))
int getMax(int arr[], int len){
	int max_num = 0;

	for (int i = 0; i < len; ++i)
		max_num = max(max_num, arr[i]);
	
	return max_num;
}

int getSum(int arr[], int len){
	int sum = 0;

	for (int i = 0; i < len; ++i)
		sum += arr[i];

	return sum;
}

int getPainterNum(int arr[], int len, int val){
	int painter = 0;
	int sum_partial = arr[0];
	
	for (int i = 1; i < len; ++i){
		sum_partial += arr[i];
		if (sum_partial > val){
			sum_partial = arr[i];
			++painter;
		}
	} 

	return painter;
}

int partition_linear(int arr[], int len, int k){
	int lo = getMax(arr, len);
	int hi = getSum(arr, len);

	while (lo < hi){
		int mid = lo + (hi - lo)/2;
		int num = getPainterNum(arr, len, mid);
		if (num < k)
			hi = mid + 1;
		else
			lo = mid;
	}

	return lo;
}
