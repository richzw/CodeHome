const int Num = 100, Wt = 1000;
int cost[Num] = {4, 2, 2, 1, 10}; 
int weight[Wt] = {12, 2, 1, 1, 4};
int c[Wt+1];
void knapsack(int n, int w){
  memset(c, 0, sizeof(c));

	for (int i = 0; i < n; ++i)
		for (int j = w; j - weight[i] > 0; --j)
			c[j] = max(c[j], c[j-weight[i]]+cost[i]);
	cout << "the max weight " << c[w];

}
