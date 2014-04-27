/*
Q:给定大小为n的数组A，A中的元素有正有负。请给出方法，对其排序，保证：
	* 负数在前面，正数在后面
	* 正数之间相对位置不变
	* 负数之间相对位置不变
能够做到时间复杂度为O(n)，空间复杂度为O(1)么

这类题目，还有其他的变形，比如，数组A有奇数和偶数，排序奇数在前偶数在后，并且奇数和偶数内部的相对顺序不能变。
那么这类的题目，该如何解决呢？
首先，暴力法可行：从左到右扫描数组，遇到第一个负数，与其前面的每一个元素进行交换，直到第一个位置，这里并不能直接交换，
因为这样就改变了正数的相对位置了。后面的继续扫描，第二个负数，依次交换到第二个位置。依次类推。算法总的时间复杂度为O(n^2)。
上面这个方法，大多数同学，都可以给出。

设两个指针positive, negative，初始指向数组最后一个元素，然后从后往前遍历数组，
positive每次指向第一个满足positive<negative的正数，negative指向最后一个负数，然后将positive+1到negative的元素往前移,
将positive移至negative位置。循环上述过程,直至positive<0.时空复杂度分别是O(n),O(1)

那么，是否有更快的方法呢？大家请看下面的方法：
	* 统计负数的个数，设为M
	* 找到索引k>M的第一个负数
	* 使用i和j两个索引，i从0开始，直到遇到第一个正数，j从k开始，直到遇到第一个负数。交换i，j位置上的数，然后符号取反
	* 对于A[0,M]和A[M, n]分别执行上面三步
	* 修正符号：前面的M个为负数，后面的为正数。
下面举例来说明，对于数组{-1,1,3,-2,2}，根据描述，有M=2，k=3。i遇到第一个正数为A[1]=1，j遇到第一个负数为A[3]=-2。
然后交换i和j位置上的值， 数组变为{-1, -2, 3, 1, 2},  然后改变符号，得到{-1,2,3,-1,2}。然后递归处理{-1,2},{3,-1,2}，
最终得到{-1,2,1,-3,2}。进行最后一步，修正符号, 得到{-1,-2,1,3,2}。即为最终答案。这个方法是nlog(n)的，比上面的提高了一些。
*/

void stable_01_recur(int arr[], int begin, int end){
	if (begin >= end)
		return;

	int negative_num = 0;
	int i = 0, j = 0;

	for (i = 0; i < (end-begin); ++i)
		if (arr[i] < 0)
			negative_num++;
	
	if (negative_num != 1 || arr[begin] > 0){
		i = begin;  //point to the first positive
		j = negative_num; // point to the first negative after negative_num
		
		while (i < end){
			if (arr[i] > 0)
				break;
			else
				++i;
		}
		while (j < end){
			if (arr[j] < 0)
				break;
			else
				j++;
		}

		swap(arr[i], arr[j]);
		arr[i] = -arr[i];
		arr[j] = -arr[j];

		if (negative_num > 1){
			stable_01_recur(arr, 0, negative_num);
			stable_01_recur(arr, negative_num, end);
		}
	}

	//amend the sign
	for (int index = 0; index < (end-begin); ++index){
		if (((index < negative_num) && (arr[index] > 0)) ||
			((index >= negative_num) && (arr[index] < 0)))
				arr[index] = -arr[index];
	}
}
void stable_01(int arr[], int len){
	stable_01_recur(arr, 0, len);
}
