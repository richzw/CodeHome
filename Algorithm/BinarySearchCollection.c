/*
1. 给定一个有序（非降序）数组A，求任意一个i使得A[i]等于target，不存在则返回-1
2. 给定一个有序（非降序）数组A，可含有重复元素，求最小的i使得A[i]等于target，不存在则返回-1
3. 给定一个有序（非降序）数组A，可含有重复元素，求最大的i使得A[i]等于target，不存在则返回-1
4. 给定一个有序（非降序）数组A，可含有重复元素，求最大的i使得A[i]小于target，不存在则返回-1
5. 给定一个有序（非降序）数组A，可含有重复元素，求最小的i使得A[i]大于target，不存在则返回-1
6. 给定一个有序（非降序）数组A，可含有重复元素，求target在数组中出现的次数。
7. 给定一个有序（非降序）数组A，若target在数组中出现，返回位置，若不存在，返回它应该插入的位置。
8. 给定一个有序（非降序）数组A，可含有重复元素，求绝对值最小的元素的位置
9. 给定一个有序（非降序）数组A和一个有序（非降序）数组B，可含有重复元素，求两个数组合并结果中的第k(k>=0)个数字。
10. 一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求target在变化后的数组中出现的位置，不存在则返回-1.
11. 一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求最小值所在位置
12. 一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求第k(k > 0)小元素
*/

//给定一个有序（非降序）数组A，可含有重复元素，求最大的i使得A[i]小于target，不存在则返回-1。
int searchLastPosLessThan(int A[], int n, int target){
	if (n <= 0)
		return -1;

	int low = 0, high = n - 1;
	while (low < high){
		int mid = low + (high - low + 1) >> 1; // avoid bad loop
		if (A[mid] < target)
			low = mid;
		else
			high = mid - 1;
	}

	return A[low] < target? low : -1;
}

// 给定一个有序（非降序）数组A，可含有重复元素，求target在数组中出现的次数
int count(int A[], int n, int target)
{
	int firstPos = binary_search_first_position(A, n, target); 
	if(firstPos == -1)
		return 0;
	int lastPos = binary_search_last_position(A, n, target); 

	return lastPos-firstPos+1;  // 出现次数
}

/* 给定一个有序（非降序）数组A，若target在数组中出现，返回位置，若不存在，返回它应该插入的位置

[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0 */
int searchInsert(int A[], int n, int target){
	if (A[n-1] < target)
		return n-1;

	int low = 0, high = n - 1;
	while (low < high){
		int mid = low + (high - low)>>2;
		if (A[mid] >= target)
			high = mid;
		else
			low = mid+1;  // A[mid] < target  
	}

	return high;
}

/*
给定一个有序（非降序）数组A，可含有重复元素，求绝对值最小的元素的位置
*/
int searchMinAbs(int A[], int n, int target){
	int low = 0, high = n-1;

	while (low < high){
		int mid = low + (high - low)>>1;
		if (A[mid] < 0)
			low = mid + 1;
		else  //A[mid] >= 0
			high = mid;
	}

	if (low > 0 && abs(A[low-1]) < abs(A[low]))
		return low-1;
	else
		return low;
}

/*
给定一个有序（非降序）数组A和一个有序（非降序）数组B，可含有重复元素，求两个数组合并结果中的第k(k>=0)个数字。
*/
int findKthFromTwoArrays(int A[], int m, int B[], int n, int k){
	if (m == 0)
		return B[k];
	if (n == 0)
		return A[k];

	int mid_a = (m-1)>>1;
	int mid_b = (n-1)>>1;

	if (A[mid_a] <= B[mid_b]){
		if (k < mid_a+1+mid_b+1){
			/*
			设x为数组A和数组B中小于B[j]的元素数目，则i+1+j+1小于等于x，
			因为A[i+1]到A[m-1]中还可能存在小于等于B[j]的元素；
			如果k小于i+1+j+1，那么要查找的第k个元素肯定小于等于B[j]，
			因为x大于等于i+1+j+1；既然第k个元素小于等于B[j]，那么只
			需要在A[0]~A[m-1]和B[0]~B[j]中查找第k个元素即可，递归调用下去。
			*/
			if (mid_b > 1)
				return findKthFromTwoArrays(A, m, B, mid_b, k);
			else{ // mid_b == 0
				if (k == 0)
					return min(A[0], B[0]);
				else if (k == m)
					return max(A[m-1], B[0]);
				else
					return A[k] < B[0] ? A[k] : max(A[k-1], B[0]);
			}
		}else{
			/*
			设y为数组A和数组B中小于于等于A[i]的元素数目，则i+1+j+1大于等于y；
			如果k大于等于i+1+j+1，那么要查找到第k个元素肯定大于A[i]，因为
			i+1+j+1大于等于y；既然第k个元素大于A[i]，那么只需要在A[i+1]~A[m-1]
			和B[0]~B[n-1]中查找第k-i-1个元素，递归调用下去。
			*/
			return findKthFromTwoArrays(A+mid_a+1, m-mid_a-1, B, n, k-mid_a-1);
		}
	}else{
		return findKthFromTwoArrays(B, n, A, m, k);
	}
}

/*
一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求target在变化后的数组中出现的位置，不存在则返回-1
*/
int searchInRotateArr(int A[], int n, int target){
	int low = 0, high = n - 1;

	while (low <= high){
		int mid = low + (high - low)>>1;
		if (A[mid] == target)
			return mid;
		else if (A[mid] > target){
			// low ... mid is ascending order
			if (target >= A[low] && target < A[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}else {
			// mid ... high is ascending order
			if (target >= A[mid] && target < A[high])
				low = mid + 1;
			else
				high = mid - 1;
		}
	}

	return -1;
}

/*
一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求最小值所在位置
*/
int searchMinFromRotateArr(int A[], int n, int target){
	if (n == 1)
		return 0;

	int low = 0, high = n-1;

	while (low < high - 1){
		int mid = low + (high - low)>>1;

		if (A[mid] < A[low])
			high = mid;
		else
			low = mid;
	}

	return (A[low] < A[low+1])?low:low+1;
}

/*
一个有序（升序）数组，没有重复元素，在某一个位置发生了旋转后，求第k(k > 0)小元素的位置
*/
int searchKthInRotatedArray(int A[], int n, int k) 
{
	int posMin = searchMinFromRotateArr(A, n, k);
	return (posMin+k-1)%n;
}
