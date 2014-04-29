/*
1. 将n划分成若干正整数之和的划分数。
2. 将n划分成k个正整数之和的划分数。
3. 将n划分成最大数不超过k的划分数。
4. 将n划分成若干个奇正整数之和的划分数。
5. 将n划分成若干不同整数之和的划分数。
*/

// For question 1
// Integer Partition...
// naive method, recursive version
unsigned long GetPartitionCount(int n, int max){
	if (n == 1 || max == 1)
		return 1;
	else if (n < max)
		return GetPartitionCount(n, n);
	else if (n == max)
		return 1 + GetPartitionCount(n, max-1);
	else
		return GetPartitionCount(n, max-1)+GetPartitionCount(n-max, max);
}

// memorize version
int table[100][100]={0};

int partition(int sum, int largestNumber){
    if (largestNumber==0)
        return 0;
    if (sum==0)
        return 1;
    if (sum<0)
        return 0;

    if (table[sum][largestNumber]!=0)
        return table[sum][largestNumber];

    table[sum][largestNumber]=partition(sum,largestNumber-1) + partition(sum-largestNumber,largestNumber);
    return table[sum][largestNumber];
}

