//Q: You are working on a platform that has a very fast, hardwareaccelerated
//   sort routine. The routine, shakySort(), is not stable, but you need
//   to perform a fast, stable sort. Write code that uses shakySort() to perform a stable sort. 

// Hint: multi-key sort



// sort collections
 void insertSort(int a[], int len){
     for (int j = 1; j < len; ++j){
         int key = a[j];
         int i = j - 1;
         while(i >= 0 && a[i] > key){
             a[i+1] = a[i];
             i--;
         }
         a[i+1] = key;
     }
 }

 void insertSort_recursive(int a[], int len){
     if (len <= 1) return;
     insertSort_recursive(a, len-1);
     int key = a[len-1];
     int i = len - 2;
     while(i >= 0 && a[i] > key){
         a[i+1] = a[i];
         --i;
     }
     a[i+1] = key;
 }

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
