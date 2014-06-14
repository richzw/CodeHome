void comb_sort(int arr[], int len){
	assert(arr != NULL && len > 0);
	float shrink_fac = 1.24733;
	int gap = len, swapped = 1;
	int idx = 0;
	
	while (gap>1 || swapped){
		if (gap > 1)
			gap = gap/shrink_fac;
		swapped = 0, idx = 0;
		
		while ((gap+idx) < len){
			if (arr[idx] > arr[idx + gap]){
				// swap those two elements
				int tmp = arr[idx];
				arr[idx] = arr[idx+gap];
				arr[idx+gap] = tmp;
				swapped = 1;
			}
			++idx;
		}
	}
}
