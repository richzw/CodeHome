// binary search
int binary_search(int* A, int n, int target){
	int low = 0, high = n-1;
	assert(A != NULL && n >= 0);
	while (low <= high){
		int mid = low + (high - low)/2;
		if (A[mid] == target)
			return mid;
		else if (A[mid] < target)
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}

int binary_search_imp(int* A, int n, int target){
	int low = 0, high = n;

	while (low < high){
		int mid = low + (high - low)/2;
		if (A[mid] < target)
			low = mid + 1;
		else
			high = mid;
	}

	if (low >= n || A[low] != target)
		return -low-1;
	else
		return low;
}

int binary_search_first_position(int *A, int n, int target) {
	int end[2] = { -1, n };
	while (end[0] + 1 < end[1]) {
		int mid = (end[0] + end[1]) / 2;
		int sign = (unsigned)(A[mid] - target) >> 31;
		end[1-sign] = mid;
	}
	int high = end[1];
	if (high >= n || A[high] != target)
		return -high - 1;
	else
		return high;
}
