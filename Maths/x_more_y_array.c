/*
Q:给定两个数组X和Y，元素都是正数。请找出满足如下条件的数对的数目：​
        1. x^y > y^x，即x的y次方>y的x次方​
        2. x来自X数组，y来自Y数组

假设数组X的长度为m，数组Y的长度为n，最直接的暴力法，时间复杂度为O(m*n)，但这样的话，并不需要都是正数这个条件的。
那么，我们该如何优化呢？​x^y>y^x，对于x和y来讲，有什么规律呢？该如何发现呢？
这里其实有规律的，大多数的条件下，当y>x的时候，x^y>y^x，但是有一些例外，1，2，3，4几个数，需要特殊的考虑，
比如2^4=4^2。这个大家可以通过在纸上写写画画来得到，相对繁琐，我们就不进一步分析了。​
我们可否对于原式做一些数学变换呢？使得式子变化简单。如何去做呢？这个式子的复杂体现在两边都是指数的形式，如何变化一下呢？
我们很自然的就想到，逆运算对数运算，则，两边取对数可得：ylog(x)>xlog(y)。
这里同学们可能要问，可以直接取对数么？取对数之后，大小关系仍旧满足么？这里是有两点保证的：​
        1. 对数函数的性质，单调递增​
        2. 题目中的说明：元素都是正数
对于式子:ylog(x)>xlog(y)，x和y都是正数，则进一步有：两边同时除以xy，则：log(x)/x >log(y)/y。这个式子，看起来也复杂，
但是，x和y都在各自的一边，要简单的多。​对于log(x)/x >log(y)/y，​
        1. 数组X和Y分别计算log(x)/x,log(y)/y​
        2. 然后对Y进行排序O(nlogn)​
        3. 遍历X数组，对于每一个x，在Y中，进行二分查找，即可。​
总的时间复杂度为O(nlogn + mlogn).
*/
int compare (const void* a, const void* b)
{
  return (*(float*)a - *(float*)b);
}

int get_number_pair(int x[], int xlen, int y[], int ylen)
{
	int index = 0;
	float* px = new float[xlen];
	float* py = new float[ylen];

	for (index = 0; index < xlen; ++index){
		px[index] = log((float)x[index])/x[index];
	}
	for (index = 0; index < ylen; ++index){
		py[index] = log((float)y[index])/y[index];
	}

	qsort(px, xlen, sizeof(float), compare);
	qsort(py, ylen, sizeof(float), compare);

	int paire_num = 0;
	for (index = 0; index < xlen; ++index){
		int left = 0; 
		int right = ylen;
		int mid = 0;
		while (left < right){
			mid = (left + right) >> 1;
			if (px[index] > py[mid]){
				if (px[index] < py[mid-1])
					break;
				else
					right = mid - 1;
			}else if (px[index] < py[mid]){
				if (px[index] > py[mid])
					break;
				else
					left = mid + 1;
			}else{
				break;
			}
		}
		paire_num += ylen - mid;
	}

	return paire_num;
}
