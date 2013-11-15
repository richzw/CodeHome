/*
Q:数组A中，除了某一个数字x之外，其他数字都出现了三次，而x出现了一次。请给出最快的方法，找到x。

    采用hashmap，时间复杂度O(n)，空间复杂度O(n)
    对数组A进行排序，然后在遍历一次，时间复杂度O(nlogn)，空间复杂度O(1)
题目中，如果数组中的元素都是三个三个出现的，那么从二进制表示的角度，每个位上的1加起来，应该可以整除3。
如果有一个数x只出现一次，会是什么情况呢？
    如果某个特定位上的1加起来，可以被3整除，说明对应x的那位是0，因为如果是1，不可能被3整除
    如果某个特定位上的1加起来，不可以被3整除，说明对应x的那位是1
根据上面的描述，我们可以开辟一个大小为32的数组，第0个元素表示，A中所有元素的二进制表示的最低位的和，依次类推。
最后，再转换为十进制数即可。这里要说明的是，用一个大小为32的整数数组表示，同样空间是O(1)的
*/
int get_high_bit_one(int num){
	for (int i = 31; i >=0; --i){
		if (!(num & (1<<i)))
			continue;
		return i;
	}
}

int find_once_number(int arr[], int len){
	int* bit_arr = new int[32];
	int num = 0;

	if (bit_arr != NULL){
		memset(bit_arr, 0, 32*sizeof(int));

		for (int index = 0; index < len; ++index){
			int bit_nums = get_high_bit_one(arr[index]);
			for (int bit_idx = 0; bit_idx <= bit_nums; ++bit_idx){
				bit_arr[bit_idx] +=  (arr[index] & (1<<bit_idx))>>bit_idx;
			}
		}

		for (int i = 0; i < 32; ++i){
			if (bit_arr[i]%3)
				bit_arr[i] = 1;
			else
				bit_arr[i] = 0;
		}

		for (int i = 0; i < 32; ++i){
			num += bit_arr[i]*(1<<i);
		}

		delete[] bit_arr;
	}
	return num;
}
