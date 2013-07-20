/*
Q: 给定一个数组，我们可以找到两个不相交的、并且是连续的子数组A和B，A中的数字和为sum(A), B中的元素和为sum(B)。
找到这样的A和B，满足sum(A) - sum(B)的绝对值是最大的。 
例如：[2, -1 -2, 1, -4, 2, 8]划分为A=[-1, -2, 1, -4], B=[2, 8]， 最大的值为16
*/

/*
    从左向右遍历数组，计算max_left和min_left数组，O(n)时间复杂度
    从右向左遍历数组，计算max_right和min_right数组，O(n)时间复杂度
    然后对于每一个i，i从1开始到n-1,计算max_left[i - 1] - min_right[i], max_right[i] - min_left[i - 1]。选取绝对值最大的。
方法的整体空间复杂度为O(n),时间复杂度也是O(n)。
*/


int getMaxDvalueOfSubArray(int arr[], int len){
  int max_until[20] = {0};
	int min_until[20] = {0};

	int left_max[20] = {0};
	int left_min[20] = {0};
	left_max[0] = left_min[0] = arr[0];
	max_until[0] = min_until[0] = arr[0];
	int maxsofar = 0, minsofar = 0;
	// from left to right
	for (int index = 1; index < len; ++index){
		// compute the max sub array
		if ((arr[index] + max_until[index-1])> max_until[index-1] &&
			(arr[index] + max_until[index-1])> arr[index]){
			max_until[index] = max_until[index-1]+arr[index];
		}else{
			max_until[index] = arr[index];
		}
		left_max[index] = max(max_until[index], maxsofar);
		maxsofar = (maxsofar > left_max[index])? (maxsofar):(left_max[index]);

		//compute the min sub array
		if ((arr[index] + min_until[index-1]) < min_until[index-1] &&
			(arr[index] + min_until[index-1]) < arr[index]){
			min_until[index] = min_until[index-1]+arr[index];
		}else{
			min_until[index] = arr[index];
		}
		left_min[index] = min(min_until[index], minsofar);
		minsofar = (minsofar < left_min[index])? (minsofar):(left_min[index]);
	}

	int right_max[20] = {0};
	int right_min[20] = {0};
	right_max[len-1] = right_min[len-1] = arr[len-1];
	max_until[len-1] = min_until[len-1] = arr[len-1];
	maxsofar = 0, minsofar = 0;
	// from right to left
	for (int index = len-1; index > 0; ++index){
		// compute the max sub array
		if ((arr[index] + max_until[index-1])> max_until[index-1] &&
			(arr[index] + max_until[index-1])> arr[index]){
			max_until[index] = max_until[index-1]+arr[index];
		}else{
			max_until[index] = arr[index];
		}
		left_max[index] = max(max_until[index], maxsofar);
		maxsofar = (maxsofar > left_max[index])? (maxsofar):(left_max[index]);

		//compute the min sub array
		if ((arr[index] + min_until[index-1]) < min_until[index-1] &&
			(arr[index] + min_until[index-1]) < arr[index]){
			min_until[index] = min_until[index-1]+arr[index];
		}else{
			min_until[index] = arr[index];
		}
		left_min[index] = min(min_until[index], minsofar);
		minsofar = (minsofar < left_min[index])? (minsofar):(left_min[index]);	
	}

	maxsofar = 0;
	for (int i = 1; i < len; ++i){
		int val1 = abs(left_max[i - 1] - right_min[i]);
		int val2 = abs(right_max[i] - left_min[i - 1]);
		
		maxsofar = (max(val1, val2) > maxsofar)? max(val1, val2): maxsofar;
	}

	return maxsofar;
}
