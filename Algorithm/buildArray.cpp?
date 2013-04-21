/*
 Q: Given array a [n],  Get array b [n] b [i] = a [0] * a [1] ... a [n-2] * a [n-1] / a [i]
    Requirements can not be used to divide
    In addition to traverse the counter with a [N] b [N], do not use the new variable 
    (including stack temporary variables, space and global static variable)
     Space complexity of O (1) time complexity of O (n)
*/

const int ARRLEN = 5;
int arr_a[ARRLEN] = {1, 2, 3, 4, 5}; 
int arr_b[ARRLEN];

//here is wrong case...
void solve_1(int arr[], int len){
 	int index = 0;
	arr_b[0] = 1;
	for (index = 0; index < len; ++index){
		arr_b[0] *= arr_a[index];
	}

	for (index = 1; index < len; ++index){
		arr_b[index] = arr_b[0] ^ arr_a[index];
	}
	arr_b[0] ^= arr_a[0];
}

/*
	arr_b[0] =      a[1]*a[2]*a[3]*a[4]
	arr_b[1] = a[0]*     a[2]*a[3]*a[4]
	arr_b[2] = a[0]*a[1]*     a[3]*a[4]
	arr_b[3] = a[0]*a[1]*a[2]*     a[4]
	arr_b[4] = a[0]*a[1]*a[2]*a[3]
*/
void solve_2(int arr[], int len){
	int index = 0;
	
	// loop from begin to end
	arr_b[0] = 1;
	for (index = 1; index < len; ++index){
		arr_b[index] = arr_b[index - 1]*arr_a[index - 1]; 
	}

	// loop from end to begin
	for (index = len-2; index > 0; --index){
		arr_b[0] *= arr_a[index + 1];
		arr_b[index] *= arr_b[0];
	}
	arr_b[0] *= arr_a[1];

	copy(arr_b, arr_b+len, ostream_iterator<int>(cout, " "));
}
