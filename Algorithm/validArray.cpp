/*
* Q: Given a length of n integer array, to check whether the following conditions are met, 
*    the adjacent digits of the absolute value of the difference can just composed of 1,2, ..., n-1. 
*    For example: 2 5 4 6 -> 1, 2, 3 established. 2 5 4 7 -> 1, 3, 3 does not hold. 
*                 1 2 3 4 -> 1, 1, 1 is not established
*/

// Solution: Get the sum of the difference of the adjacent digits, to check whether the sum is n*(n+1)/2
bool isValidArray(int arr[], int len){
  if (arr == NULL || len <= 0)
		return false;

	int difference_len = len - 1;
	int difference_sum = difference_len*(difference_len + 1)/2;
	int sum = 0;

	for (int index = 0; index < len - 1; ++index){
		int difference = arr[index+1] > arr[index] ? (arr[index+1]-arr[index]):(arr[index]-arr[index+1]);
		if (difference > difference_len)
			return false;

		sum += difference;	
		if (sum > difference_sum)
			return false;
	}

	return (sum == difference_sum);
}
