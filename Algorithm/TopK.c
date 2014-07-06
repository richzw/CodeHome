
//
int select(int arr[], int len, int k){
	radom_shuffle(arr, len);
	
	int lo = 0, hi = len - 1;
	while (hi > lo){
		int j = partition(a, lo, hi);
		
		if (j < k ) lo = j + 1;
		else if (j > k) hi = j - 1;
		else return arr[k];
	}
	return arr[k];
}
