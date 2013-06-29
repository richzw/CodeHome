
int way[Wt] = {0};
void knapsack_way(int n, int w){
  way[0] = 1;
	for (int i = n-1; i >= 0; --i)
		for (int j = w; j >=weight[i]; --j)
			if (c[j-weight[i]] + cost[i] > c[j]){
				c[j] = c[j-weight[i]] + cost[i];
				way[j] = way[j-weight[i]];
			}else if (c[j-weight[i]] + cost[i] == c[j]){
				way[j] = way[j] + way[j-weight[i]];
			}else if (c[j-weight[i]] + cost[i] < c[j]){
				//way[j] = way[j]
			}
	
	cout << "the element combine ways is: " << way[w] << endl;
}
