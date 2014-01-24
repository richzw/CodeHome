/*
Given an array A of integers, find the maximum of j-i subjected to the constraint of A[i] < A[j].
*/

// O(N^2) brute force
int GetMaxIndexDiff(int arr[], int len){
	int max_diff = -1;

	for (int i = 0; i < len; ++i){
		for (int j = len; j > i; --j){
			if (arr[j] > arr[i] && max_diff < (j - i))
				max_diff = j - i;
		}
	}

	return max_diff;
}
// O(NlogN) sort method


// to be continue... O(N) time, O(N) space
/*
To solve this problem, we need to get two optimum indexes of arr[]: left index i and right index j. 
For an element arr[i], we do not need to consider arr[i] for left index if there is an element smaller than arr[i] on left side of arr[i]. 
Similarly, if there is a greater element on right side of arr[j] then we do not need to consider this j for right index. 
*/
int maxIndexDiff(int arr[], int n)
{
    int maxDiff;
    int i, j;
 
    int LMin;
    int *RMax = (int *)malloc(sizeof(int)*n);
 
    LMin = arr[0];
 
    RMax[n-1] = arr[n-1];
    for (j = n-2; j >= 0; --j)
        RMax[j] = max(arr[j], RMax[j+1]);
 
    i = 0, j = 0, maxDiff = -1;
    while (j < n && i < n)
    {
        if (LMin < RMax[j])
        {
            maxDiff = max(maxDiff, j-i);
            j = j + 1;
        }
        else
        {
            LMin = min(LMin,arr[i+1]);
            i = i+1;
        }
    }
 
    return maxDiff;
}
