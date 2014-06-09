/*
Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm’s runtime complexity must be in the order of O(log n).
If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
*/

// binary search

int searchFirstPos(int A[], int n, int target)
{
	if(n <= 0) return -1;
	int low = 0, high = n-1;
	while(low < high)
	{
		int mid = low+((high-low)>>1);
		if(A[mid] < target)
			low = mid+1;
		else // A[mid] >= target
			high = mid;
	}

	if(A[low] != target)
		return -1;
	else
		return low;
}

int searchLastPos(int A[], int n, int target)
{	
	if(n <= 0) return -1;
	int low = 0, high = n-1;
	while(low < high)
	{
		int mid = low+((high-low+1)>>1);
		if(A[mid] > target)
			high = mid-1;
		else // A[mid] <= target
			low = mid;
	}

	if(A[high] != target)
		return -1;
	else
		return high;
}
