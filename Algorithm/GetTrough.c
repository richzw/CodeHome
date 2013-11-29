/*
//一个数组A[1...n]，满足A[1]>=A[2], A[n] >= A[n-1]。A[i]被成为波谷，意味着：A[i-1] >= A[i] <= A[i+1]。
//请给出一个算法，找到数组中的一个波谷。O(n)的方法，是很直接，有更快的方法么？
找到数组的mid元素，mid有几种情况：
        * 如果A[mid-1]>=A[mid] && A[mid+1]>=A[mid]，找到波谷；
        * 如果A[mid-1]<=A[mid]<A[mid+1]，right=mid，在左侧继续找；
        * 如果A[mid+1]<=A[mid]<A[mid-1]，left=mid，在右侧继续找；
        * 如果A[mid-1]<A[mid] && A[mid+1]<A[mid]，任意一侧都可以，任意一侧，都必将存在波谷。
*/
int get_trough(int arr[], int left, int right){
	int len = right - left;
	int trough_index = (right+left)/2;
	int trough_left = 0, trough_right = 0;

	while (left < right){
		trough_index = (right+left)/2;

		if (trough_index - 1 < 0)
			trough_left = trough_index;
		else 
			trough_left = trough_index - 1;

		if (trough_index + 1 >= len)
			trough_right = trough_index;
		else
			trough_right = trough_index + 1;

		if (arr[trough_left] >= arr[trough_index] && arr[trough_right] >= arr[trough_index])
			break;
		else if (arr[trough_left] <= arr[trough_index] && arr[trough_index] < arr[trough_right]){
			right = trough_index;
			continue;
		}else if (arr[trough_left] > arr[trough_index] && arr[trough_index] >= arr[trough_right]){
			left = trough_index;
			continue;
		}else{
			left = trough_index; // or right = trough_index;
			continue;
		}
	}

	return trough_index;
}
