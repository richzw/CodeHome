
void bubble_sort(int arr[], int len){
	assert(arr != NULL && len > 0);
	int cur_idx = len-1;
	bool moved = false;
	
	do{
		for (int i = 1; i < cur_idx; ++i){
			moved = false;
			if (arr[i] < arr[i-1]){
				//
				int tmp = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = tmp;
				
				moved = true;
			}
		}
		cur_idx--;	
	}while(moved);
	
}
