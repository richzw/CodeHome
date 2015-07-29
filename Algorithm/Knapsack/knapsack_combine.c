//背包内物品的组合方式


void find_path(int n, int w, int k);
int pl[Num][Wt] = {0}; //0 not, 1 in, 2 in or not OK.
void knapsack_combine(int n, int w){
  for (int i = n-1; i >= 0; --i)
	for (int j = w; j >=weight[i]; --j)
		if (c[j-weight[i]] + cost[i] > c[j]){
			c[j] = c[j-weight[i]] + cost[i];
			pl[i][j] = 1;
		}else if (c[j-weight[i]] + cost[i] == c[j]){
			pl[i][j] = 2;
		}else if (c[j-weight[i]] + cost[i] < c[j]){
			pl[i][j] = 0;
		}
	int k = 0;
	find_path(n-1, c[w], k);
}
int output[Num];
void find_path(int n, int w, int k){
	
	if (n < 0){
		cout << "this is one type: ";
		for (int i = 0; i < k; ++i)
			cout << output[i] << " "; 
		cout << endl;
		return;
	}

	if (pl[n][w] == 0){
		find_path(n-1, w, k);
	}else if (pl[n][w] == 1){
		output[k] = n;
		find_path(n-1, w-weight[n], k+1);
	}else if (pl[n][w] == 2){
		output[k] = n;
		find_path(n-1, w-weight[n], k+1);

		find_path(n-1, w, k);
	}
}
