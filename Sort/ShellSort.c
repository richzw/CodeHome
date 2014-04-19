
/*
* @func: shell sort implementation
* @params: arr{array},
*          left{int}, the left boundary of the array
*          right{int}, the right boundary of the array
*/
void shellsort(int arr[], int left, int right){
	int i, j, step;

	// the gaps are [1 4 13 40 121 ...], => 3*x+1 (x >= 0), by Knuth.
	for (step = 1; step <= (right - left)/9; step = 3*step + 1) ;

	for ( ; step > 0; step /= 3)
		for (i = left + step; i <= right; ++i){
			int tmp = arr[i];
			for (j = i; j >= left + step && arr[j - step] > tmp; j -= step)
				arr[j] = arr[j - step];
			arr[j] = tmp;
		}
}

void merge(int arr[], int left, int mid, int right){
	int aux[14] = {0};
	int i, j, k;

	for (i = mid+1; i > left; --i) aux[i-1] = arr[i-1];
	for (j = mid; j < right; ++j) aux[right+mid-j] = arr[j+1];
	for (k = left; k <= right; ++k)
		if (aux[j] < aux[i])
			arr[k] = aux[j--];
		else
			arr[k] = aux[i++];
}
/*
* @func: merge sort implementation
* @params: arr{array},
*          left{int}, the left boundary of the array
*          right{int}, the right boundary of the array
*/
void mergesort(int arr[], int left, int right){
	int mid = left + (right - left)/2;

	if (right <= left)
		return;

	mergesort(arr, left, mid);
	mergesort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}
