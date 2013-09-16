/*
Q: 给定未排序的数组，请给出方法找到最长的等差数列。

我们假设dp[i][j]表示以A[i]A[j]开始的数列的长度，dp[i][j]如何表示呢？dp[i][j]=dp[j][k]+1，
当 A[j]-A[i]=A[k]-A[j],及A[k]+A[i]=2*A[j]。
根据dp[i][j]的定义，我们知道dp[x][n-1]=2，也就是 最后一列是2，数列只有A[x]和A[n-1]两个元素。
首先，j从n-2，开始向前遍历，对于每一个，找到i和k，满足 A[k]+A[i]=2*A[j]，则有dp[i][j]=dp[j][k]+1，若没有，则dp[i][j]就为2.
这里找i和k，有一个小技巧，如下：初始i=j-1,k=j+1，然后分别向两边遍历，如果A[k]+A[i]>2*A[j]则i--
*/

// the input parameter arr should be one sorted array.
int lengthofLongestAP(int arr[], int len){
	if (len <= 2)
		return len;

	int** pl = new int*[len];
	for(int i = 0; i < len; ++i) {
		pl[i] = new int[len];
	}
	// fill entries in last column as 2
	for (int i = 0; i < len; ++i){
		pl[i][len-1] = 2;
	}

	int iret = 2; // initialize the result
	for (int j = len - 2; j >= 1; --j){
		int i = j - 1, k = j + 1;
		
		while (i >= 0 && k <= len - 2){
			if (arr[i] + arr[k] < 2*arr[j])
				k++;
			else if (arr[i] + arr[k] > 2*arr[j])
				pl[i][j] = 2, --i;
			else {
				pl[i][j] = pl[j][k] + 1;
				iret = max(iret, pl[i][j]);
				--i, ++k;
			}
		}

		// if the loop was stopped due to k becoming more than n-1,
		// set the remaining entties in column j as 2
		while(i >= 0){
			pl[i][j] = 2;
			--i;
		}
	}

	// release the memory...
	for(int i = 0; i < len; ++i) {
		delete[] pl[i];
	}
	delete[] pl;

	return iret;
}
