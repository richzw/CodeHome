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

// better solution, bit operation
/*
The bit operations gives me the hint and remind me about logic design. Then I started to sketch a truth table like below.
B1	B0	Input	B1`	B0`
0	0	1	0	1
0	1	1	1	0
1	0	1	0	0
0	0	0	0	0
0	1	0	0	1
1	0	0	1	0

Then the straightforward transition function for B0 and B1 is as follows:
b1' = (!b1) b0 Inp + b1(!b0)(!inp);ie. bi` is 1 when b1b0Inp is 010 or 100.
b0` = (!b1) (!b0) Inp + (!b1) b0 (!Inp); ie. b0' is 1 when b1b0Inp is 001 or 010.
*/
int singleNumber(int A[], int n) {
        int one = 0, two = 0;
        for (int i = 0; i < n; i++) {
            int one_ = (one ^ A[i]) & ~two;
            int two_ = A[i] & one | ~A[i] & two;
            one = one_;
            two = two_;
        }
        return one;
}

// another solution
/*
用ones记录到当前计算的变量为止，二进制1出现“1次”（mod 3 之后的 1）的数位。用twos记录到当前计算的变量为止，
二进制1出现“2次”（mod 3 之后的 2）的数位。当ones和twos中的某一位同时为1时表示二进制1出现3次，此时需要清零。
即用二进制模拟三进制计算。最终ones记录的是最终结果。
*/
int singleNumber(int A[], int n) {
    int ones = 0, twos = 0, xthrees = 0;
    for(int i = 0; i < n; ++i) {
        twos |= (ones & A[i]);
        ones ^= A[i];
        xthrees = ~(ones & twos);
        ones &= xthrees;
        twos &= xthrees;
    }
    return ones;
}

