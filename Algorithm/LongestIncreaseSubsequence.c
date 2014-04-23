/*
The longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a given sequence 
such that all elements of the subsequence are sorted in increasing order. 
For example, length of LIS for { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is {10, 22, 33, 50, 60, 80}.
*/

//Solution1: dp[i]=max(dp[j])+1,(j∈[1, i-1])
int LIS(int arr[1000], int n)
{
  for(int i=1; i<=n; ++i)
		dp[i] = 0;
	int max;
	dp[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		for(int j=1; j < i; ++j)
		{
			if(arr[i] > arr[j] && dp[j] + 1 > dp[i])
				dp[i] = dp[j] + 1;
		}
		if (dp[i] > max)
			max = dp[i];
	}

	return max;
}
//Solution 2: 用f[k]表示长度为k的上升子序列最后一个数最小是多少。易知数组f是递增的。读到一个新的数x后，
//找到某个i使得x>f[i]且x<=f[i+1]，于是用x去更新f[i+1]；特别地，如果所有的f[i]都小于x，则增加f的长度。f的长度即为所求。
//由于f是递增的，因此可以采用二分查找，时间复杂度为O(nlgn)
int bSearch(int num, int k)  
{  
    int low=1, high=k;  
    while(low<=high)  
    {  
        int mid=(low+high)/2;  
        if(num>=b[mid])  
            low=mid+1;  
        else   
            high=mid-1;  
    }  
    return low;  
}  
 
int LIS_bak()
{
	int low = 1, high = n;
	int k = 1;
	b[1] = p[1];
	for(int i=2; i<=n; ++i)
	{
		if(p[i]>=b[k])
			b[++k] = p[i];
		else
		{
			int pos = bSearch(p[i], k);
			b[pos] = p[i];
		}
	}
	return k;
}
