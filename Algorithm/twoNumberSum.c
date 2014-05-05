/*
Given an integer x and an unsorted array of integers, describe an algorithm to 
determine whether two of the numbers add up to x. (In this case, say that the interviewer hates hash tables.)
*/

//solution A:
/*Sort the array. Then, keep track of two pointers in the array, one at
the beginning and one at the end. Whenever the sum of the current two integers is
less than x, move the first pointer forwards, and whenever the sum is greater than x,
move the second pointer backwards. If you cannot find two numbers that add to x
before one of the pointers meet, then there is no pair of integers that sum to x. This
solution takes O(n log n) time because we sort the numbers.*/
int compare(const void * a, const void * b){
	return (*(int*)b - *(int*)a);
}

bool hasTwoNumbers_pointers(int arr[], int len, int sum){
	if (arr == NULL || len <= 1)
		return false;
	
	sort(arr, len, sizeof(int), compare);
	
	int first = 0;
	int last = len-1;
	while (first < last){
		if (arr[first] + arr[last] == sum)
			return true;
		else if (arr[first] + arr[last] < sum) // move the header
			++first;
		else if (arr[first] + arr[last] > sum) // move the tailer
			--last;
	}
	return false;
}


//solution B:
/*Create a binary search tree containing x minus each element
in the array. Then, check whether any element of the array appears in the BST. It
takes O(n log n) time to create a binary search tree from an array, since it takes
O(log n) time to insert something into a BST, and it takes O(n log n) time to see if
any element in an array is in a BST, since the lookup time for each element in the
array takes O(log n). Therefore step one takes O(n log n) time and step two takes
O(n log n) time, so our total running time is O(n log n).*/

bool hasTwoNumbers_bst(int arr[], int len, int sum){
	if (arr == NULL || len <= 1)
		return false;
		
	set<int> bst;
	// build the bst
	for (int idx = 0; idx < len; ++idx)
		bst.insert(sum-arr[idx]);
	
	for (int idx = 0; idx < len; ++idx){
		if (bst.find(arr[idx]) != bst.end()){
			return true;
		}
	}
	return false;
}
