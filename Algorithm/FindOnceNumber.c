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

//更好的方法，而且可以扩展到多位计算的方法。
int getSingleNumber_v2(int a[], int len){
	if (a == NULL)
		return 0;
	int x0 = ~0, x1 = 0, x2 = 0, tmp;
	for (int i = 0; i < len; ++i){
		tmp = x2;
		x2 = (x1 & a[i]) | (x2 & ~a[i]);
        x1 = (x0 & a[i]) | (x1 & ~a[i]);
        x0 = (tmp & a[i]) | (x0 & ~a[i]);
	}
	return x1;
}
//利用上述方法可以解决这个扩展问题：
//Q:Given an array of integers, every element appears k times except for one. Find that single one who appears l times.
int getSingleNumber_v3(int A[], int len, int k, int l){
    if (A == NULL) return 0;
    int t;
    int* x = new int[k];
	memset(x, 0, k*sizeof(int));
    x[0] = ~0;

    for (int i = 0; i < len; i++) {
        t = x[k-1];
        for (int j = k-1; j > 0; j--) {
            x[j] = (x[j-1] & A[i]) | (x[j] & ~A[i]);
        }
        x[0] = (t & A[i]) | (x[0] & ~A[i]);
    }
    return x[l];
}


/*
扩展一：
给定一个包含n个整数的数组，除了一个数出现二次外所有的整数均出现三次，找出这个只出现二次的整数。ones记录1出现一次的数，
twos记录1出现2次的数，容易知道twos记录的即是最终结果。
扩展二：
给定一个包含n个整数的数组，有一个整数x出现b次，一个整数y出现c次，其他所有的数均出现a次，其中b和c均不是a的倍数，找出x和y。
使用二 进制模拟a进制，累计二进制位1出现的次数，当次数达到a时，对其清零，这样可以得到b mod a次x，c mod a次y的累加。
遍历剩余结果（用ones、twos、fours...变量表示）中每一位二进制位1出现的次数，如果次数为b mod a 或者 c mod a，
可以说明x和y的当前二进制位不同（一个为0，另一个为1），据此二进制位将原数组分成两组， 一组该二进制位为1，
另一组该二进制位为0。这样问题变成“除了一个整数出现a1次（a1 = b 或 a1 = c）外所有的整数均出现a次”，
使用和上面相同的方式计算就可以得到最终结果，假设模拟a进制计算过程中使用的变量为ones、twos、 fours...那么最终结果可以用ones | twos | fours ...表示。
*/
