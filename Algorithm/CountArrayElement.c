/*
Q:给定数组A，大小为n，数组元素为1到n的数字，不过有的数字出现了多次，有的数字没有出现。请给出算法和程序，
统计哪些数字没有出现，哪些数字出现了多少次。能够在O(n)的时间复杂度，O(1)的空间复杂度要求下完成么？
*/

/*
首先，我们介绍一种三次遍历数组的方法,我们都考虑数组从0开始：
	* 第一次遍历：对于每一个A[i] = A[i] * n
	* 第二次遍历：对于每一个i，A[A[i]/n]++
	 第三次遍历：对于每一个i，A[i] % n就是出现次数

A[i]应该出现在A中的A[i]位置，乘以n、再除以n，很容易的来回变换；第二次遍历，对于A[i]本来所在的位置不断增1，
但绝对不对超出n的，那每一个i出现的次数，就是A[i]对n取余。
还有一种两次遍历的方法，也是上面的思路：题目中数组是1到n，为了方便算法考虑，以及数组存储方便，我们考虑0-n-1，结果是相同的。
考虑A[i]，现在位置是i，如果采用A来计数，它的位置应该是A[i] % n，找到计数位置，该如何处理这个位置呢？加1么？
显然不可以，这里有一个技巧，就是加n，有两个原因
	* 加n可以保证A[i] % n是不变的
	* A数组，最后每一个元素表示为A[i] = x + k*n，其中x<n，并且k就是我们要统计的频率。
*/

void get_repetition(int a[], int n){
	int i = 0, frequency = 0, element = 0;

	for (i = 0; i < n; ++i)
		a[a[i]%n] += n;
	for (i = 0; i < n; ++i){
		frequency = a[i]/n;
		element = i;
		printf("element = %d, frequency = %d", element, frequency);
	}
}
