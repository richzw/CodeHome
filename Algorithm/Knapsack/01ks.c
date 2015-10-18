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

def knapsack_onearray(v, w, limit, n):
     F = [0]*(limit + 1)
     for i in range(n):
         for j in range(limit, w[i], -1):
             F[j] = max(F[j-w[i]] + v[i], F[j])
 
     return F[:-1] 
