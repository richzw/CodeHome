/*
Given an array, describe an algorithm to identify the subarray with the maximum
sum. For example, if the input is [1, ‐3, 5, ‐2, 9, ‐8, ‐6, 4], the output would be [5, ‐ 2,9].
*/

Observe that the sum of a subarray from element i to element j is
equal to the sum of the subarray from element 1 to element j minus the subarray
from element 1 to element i ‐ 1. Our algorithm will iterate through the array. The
algorithm keeps track of the sum x of the elements no later than the element. It will
also keep track of the minimum sum y of the subarray from the first element to an
element no later than the current element. 
Finally, It will also keep track of the subarray z with the maximum sum so far. At each step,
we update x by adding the current element to it. We update y by checking whether x < y; if so, we set y to be x. 
We update z by checking whether y ‐ x is greater than z; if so, we set z to be y ‐ x.
For example, with the sample input, our algorithm would do the following:

Current element | x  | y  | z
----------------------------------
              1 | 1  | 0  | 1
             -3 | -2 | -2 | 0
              5 | 3  | -2 | 5
             -2 | 1  | -2 | 5
              9 | 10 | -2 | 12
             -8 | 2  | -2 | 12
             -6 | -4 | -4 | 12
              4 | 0  | -4 | 12


int find_max_sub_array(int arr[], int len){
	int max_sum = 0;

	int sub_sum = 0, y = 0;

	for (int index = 0; index < len; ++index){
		sub_sum += arr[index];
		if (sub_sum < y)
			y = sub_sum;

		if (sub_sum-y > max_sum)
			max_sum = sub_sum-y;
	}

	return max_sum;
}
