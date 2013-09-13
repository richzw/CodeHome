/*
Q:给定长度为n的整数数列：a0,a1,..,an-1，以及整数S。这个数列会有连续的子序列的整数总和大于S的，求这些数列中，最小的长度。

如果只是像题目这样的描述，没有强调正数，可以采用O(n^2)的方法。但是，很多同学在讨论的时候，指出了如果是正数，
解法将会有什么样的变化。这个很好。不考虑正负的O(n^2)的方法，这里不详细说了，我们来讨论，当数列中都是正数的情况。
介绍一个利用排序+二分的方法。对于子序列ai...at，子序列和s=ai+...+at=sum[t]-sum[i-1]。sum[t]表示数列a0...at的和。
那么，数组sum天然就是递增的，可以进行二分查找。 
那么如何进行二分查找呢？对于数组sum，遍历找到第一个k，sum[k]>S，二分查找k前面的某一个j，j是sum[k]-sum[j]>S里最大的一个，
则k-j是最小的。依次遍历完数组。 可以得到最小的长度，整体的时间复杂度O(nlogn)，空间复杂度为O(n)。
是否有更快的方法呢？从以上两个方法，我们可以有如下的观察：
	* a0...at>S，则a0...at+1无需再考虑
	* 对于a0...at>S，只需尝试a1...at是否>S，如果大于S，则更新最短长度。
	* 如果不大于S，大于S的只可能是a1...atat+1等。

设置索引i，j指向第一个整数：
	1. ++j，直到sum[j]-sum[i]>S，这里不需要额外保存sum，为了方便说明。记录子序列长度
	2. ++i，如果sum[j]-sum[i]>S，更新最小子序列长度。直到sum[j]-sum[i]<=S。
	3. ++j，直到sum[j]-sum[i]>S。重复上面的两步，直到数组遍历完毕。
*/

int find_min_length(int arr[], int len, int sum){
	int i = 0, j = 0;
	int min_len = len;
	int sub_sum = 0;

	while(j < len){
		sub_sum += arr[j];
		while (sub_sum > sum){
			sub_sum -= arr[i];
			if (sub_sum == sum && j - i < min_len){
				min_len = j - i;
			}else if(sub_sum < sum){
				break;
			}
			++i;
		}
		++j;
	}

	return min_len;
}
