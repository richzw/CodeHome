//
void gnome_sort(int arr[], int len){
	assert(arr != NULL && len > 0);
	int idx = 1;
	
	while(idx < len){
		if (idx == 0 || arr[idx-1] <= arr[idx])
			idx++;
		else {
			int tmp = arr[i];
			arr[i] = arr[i-1];
			arr[i--] = tmp;
		}
	}
}
