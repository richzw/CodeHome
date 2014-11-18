// search element in Yang tableau
// a[i][j]<a[i+1][j] and a[i][j]<a[i][j+1]
int findValueInYangTableau(int* matrix, int row, int col, int target){
	int i = 0;
	int j = col-1;

	while (i < row && j >= 0){
		if (target > *((matrix + i*row) + j))
			i++;
		else if (target < *((matrix + i*row) + j))
			j--;
		else
			return target;
	}

	return -1; // not find 
}

/*
令Aij为矩阵的中间元素，按照这个元素将矩阵划为4份，如果num大于Aij，则num可能落在左下、右上、右下三个子矩阵，对它们分别求子问题。
小于时也是类似的讨论。每次都会求三次子问题，每个子问题元素个数是上次的1/4，所以复杂度是f(N)=3f(N/4)+c，其中N=m*n是元素个数，c是大于0的常量，
主方法可求复杂度为O(N^(log4为底3))，计算器大概算了一下log4为底3约等于0.8。所以复杂度为O((m*n)^0.8)
*/
