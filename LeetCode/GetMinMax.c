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

/*
T(1) = 0
T(2) = 1
T(n) = T(floor(n/2)) + T(ceil(n/2)) + 2  ~ 2(T(n/2) + 2 =  1.5n -2 
*/
typedef struct Pair{
	int min;
	int max;
}Pair;

Pair GetMinMax_recv(int arr[], int low, int high){
	Pair result;

	if (high == low){
		result.min = arr[low];
		result.max = arr[low];
		return result;
	}

	if (high == low + 1){
		if (arr[low] > arr[high]){
			result.min = arr[high];
			result.max = arr[low];
		}else{
			result.min = arr[low];
			result.max = arr[high];
		}
		return result;
	}

	int mid = low + (high - low)/2;
	Pair left = GetMinMax_recv(arr, low, mid);
	Pair right = GetMinMax_recv(arr, mid, high);
	if (left.min < right.min){
		result.min = left.min;
	}else{
		result.min = right.min;
	}

	if (left.max > right.max){
		result.max = left.max;
	}else{
		result.max = right.max;
	}

	return result;
}

void GetMinMax_v1(int arr[], int len){
	if (arr == NULL || len < 1)
		return ;	

	GetMinMax_recv(arr, 0, len-1);
}
