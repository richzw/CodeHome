int partition(int arr[], int low, int high){
	int pivot = arr[high];
	int swapIdx = low;
	
	for (int idx = low; idx < high; ++idx){
		if (arr[idx] < pivot){
			swap(arr[idx], arr[swapIdx]);
			++swapIdx;
		}
	}
	
	swap(arr[swapIdx], arr[right]);
	return swapIdx;
}

//
int select(int arr[], int len, int k){
	if (k < 0 || k > len)
		return -1;
	if (len == 0)
		return arr[left];
	
	radom_shuffle(arr, len); // to make the key random so get high performance of partition.
	
	int lo = 0, hi = len - 1;
	while (hi > lo){
		int j = partition(a, lo, hi);
		
		if (j < k ) lo = j + 1;
		else if (j > k) hi = j - 1;
		else return arr[k];
	}
	return arr[k];
}

// py version

