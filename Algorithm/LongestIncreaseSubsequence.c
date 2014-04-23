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

/* cpp version
    if(n <= 0) return 0;  
    vector<int> maxV;  
    maxV.push_back(a[0]);  
    for(int i=0; i<n; ++i)  
    {  
        if(a[i] > *maxV.rbegin())  
            maxV.push_back(a[i]);  
        else  
            *lower_bound(maxV.begin(), maxV.end(), a[i]) = a[i];  
    } */
/*
examle...
假设存在一个序列d[1..9] = 2 1 5 3 6 4 8 9 7，可以看出来它的LIS长度为5。
下面一步一步试着找出它。
我们定义一个序列B，然后令 i = 1 to 9 逐个考察这个序列。
此外，我们用一个变量Len来记录现在最长算到多少了

首先，把d[1]有序地放到B里，令B[1] = 2，就是说当只有1一个数字2的时候，长度为1的LIS的最小末尾是2。这时Len=1
然后，把d[2]有序地放到B里，令B[1] = 1，就是说长度为1的LIS的最小末尾是1，d[1]=2已经没用了，很容易理解吧。这时Len=1
接着，d[3] = 5，d[3]>B[1]，所以令B[1+1]=B[2]=d[3]=5，就是说长度为2的LIS的最小末尾是5，很容易理解吧。这时候B[1..2] = 1, 5，Len＝2
再来，d[4] = 3，它正好加在1,5之间，放在1的位置显然不合适，因为1小于3，长度为1的LIS最小末尾应该是1，这样很容易推知，长度为2的LIS最小末尾是3，
于是可以把5淘汰掉，这时候B[1..2] = 1, 3，Len = 2
继续，d[5] = 6，它在3后面，因为B[2] = 3, 而6在3后面，于是很容易可以推知B[3] = 6, 这时B[1..3] = 1, 3, 6，还是很容易理解吧？ Len = 3 了噢。

*/    
  
