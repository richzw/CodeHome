/*
In Balanced Partition problem,you have a set of n integers each in the range 0 … K. 
Partition these integers into two subsets such that you minimize |S1 – S2|, 
where S1 and S2 denote the sums of the elements in each of the two subsets.
https://chinmaylokesh.wordpress.com/2011/02/10/balanced-partition-problem-finding-the-minimized-sum-between-two-partitions-of-a-set-of-positive-integers/
*/
int BalancedPartition(vector<int> v){
    int n = v.size();
    int sum = accumulate(v.begin(), v.end(), 0);
    int max_sum=sum/2,diff=INT_MAX;
    int *s = new int[sum+1];
    s[0] = 1;

    for(int i=1; i<=sum; i++) 
		s[i] = 0;
    
	for(int i=0; i<n; i++)
    {
        for(int j = sum; j>=0; j--)
        {
            if(s[j])
            {
                s[j+v[i]]+=1;
            }
        }
    }
    
	for(int j = sum/2; j>=1; j--)
        if(s[j])
        {
            return abs(sum-2*j);
        }
}

int BalancePartitionImprove(vector<int> v){
	int n = v.size();
	int sum = accumulate(v.begin(), v.end(), 0);

	vector<bool> st(sum/2+1, false);

	for (int i = 0; i < n; ++i)
		for (int j = sum/2; j >= i; --j){
			if (st[j-i])
				st[j] = true;
		}

	int halfsum = sum/2;
	for (; !st[halfsum]; halfsum--);

	return (sum - 2*halfsum);
}

void testBalancePar(){
    int value[] = {12,5,7,3};
    int n = sizeof(value)/sizeof(value[0]);
    vector<int> v(value, value+n);

    cout << BalancedPartition(v);
  //  return 0;
}
