//basic idea
/*
# of comparisons in worst case: 1 + 2(n-2) = 2n -1
# of comparisons in best case: 1 + (n–2) = n -1
# of comparisons on average: 1.5n -1
*/
void GetMinMax(int arr[], int len){
	if (arr == NULL || len < 1)
		return ;
	
	int min, max;
	if (len == 1){
		min = arr[0];
		max = arr[0];
		// cout << "max:" << max << " min:" << min <<endl;
		return;
	}

	if (arr[0] > arr[1]){
		min = arr[1];
		max = arr[0];
	}else{
		min = arr[0];
		max = arr[1];
	}

	for (int idx = 2; idx <= len-1; ++idx){
		if (min < arr[idx]){
			min = arr[idx];
		}else if (max > arr[idx]){
			max = arr[idx];
		}
	}
	
	// cout << "max:" << max << " min:" << min <<endl;
}
