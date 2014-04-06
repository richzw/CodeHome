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

void move(int* dest, int* src, int num){
	for (int index = num-1; index >= 0; --index){
		*(dest+index) = *(src+index);
	}
}

void merge_no_aux(int arr[], int left, int mid, int right){
	int first = left, last = mid + 1;
	// One extra check, can we skip the merge?
	if (arr[mid] < arr[last])
		return;

	while (first <= mid && last <= right){
		if (arr[first] <= arr[last])
			++first;
		else{
			int tmp = arr[last];
			move(arr+first+1, arr+first, last-first);
			arr[first] = tmp;
			++first;
			++mid;
			++last;
		}
	}
}

/*
* @func: merge sort from down to up method.
*/
void mergesort_BU(int arr[], int l, int r){
	for (int m = 1; m < r; m = m+m)
		for (int i = l; i <= r-m; i += m+m)
			merge(arr, i, i+m-1, min(i+m+m-1, r));
}

/*
* @func: merge sort implementation, from up to down method.
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
