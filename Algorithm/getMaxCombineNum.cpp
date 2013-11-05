/*
//给定只包含正数的数组，给出一个方法，将数组中的数拼接起来，得到的数，是最大的。 
例如： [4, 94, 9, 14, 1] 拼接之后，所得最大数为：9944141
一次排序，就得到了结果。给定例子：5,54,56
        1. 比较5和54，实际上就是比较545和554哪个大
        2. 比较5和56，实际上就是比较556和565哪个大
        3. 比较54和56，实际上就是比较5456和5654哪个大
那我们对快排程序做一下变化，当两个数字a和b进行比较时，比较的是ab和ba两个数字的大小即可。
只是比较发生了变化，剩下的和快排都是一样的。
*/

int _get_digits(int num){
	int digit_num = 1;
	
	while (num/10){
		num = num % (10^digit_num);
		++digit_num;
	}

	return digit_num;
}

bool _compare_larger(int a, int b){
	int a_digits = _get_digits(a);
	int b_digits = _get_digits(b);

	if ((a+b*pow((double)10, a_digits)) <= (b+a*pow((double)10, b_digits)))
		return true;
	else
		return false;
} 

int _partition(int arr[], int left, int right){
	int pivot = arr[left];
	int l = left, r = right;

	while (l < r){
		while (_compare_larger(arr[l], pivot) && l < right)
			++l;
		while (_compare_larger(pivot, arr[r]) && left < r)
			--r;

		if (l < r){
			int tmp = arr[left];
			arr[left] = arr[right];
			arr[right] = tmp;
		}
	}

	arr[left] = arr[r];
	arr[r] = pivot;

	return r;
}

void get_max_qsort(int arr[], int left, int right){
	if (left < right){
		int p = _partition(arr, left, right);
		get_max_qsort(arr, left, p-1);
		get_max_qsort(arr, p+1, right);
	}
}

string get_max_number(int arr[], int len){
	if (arr == NULL || len < 0)
		return 0;

	get_max_qsort(arr, 0, len-1);
	string str = "";
	for (int index = 0; index < len; ++index){
		str += std::to_string((long double)arr[index]);
	}

	return str;
}
