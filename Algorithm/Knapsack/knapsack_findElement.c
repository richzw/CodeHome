
int cost[N], weight[N];
int c[W + 1];
bool p[N][W + 1];  // indicate the element is put into the store 

void knapsack(int n, int w) 
{
  
  for (int i = 0; i < n; ++i)
    for (int j = w; j >= weight[i]; --j)
      if (c[j] < (c[j - weight[i]] + cost[i]))
      {
        c[j] = c[j - weight[i]] + cost[i];
        p[i][j] = true;
      }
      
  cout << "the max cost is " << c[w] << endl;
  
  // loop back to find all elements in the bagage
  for (int i = n-1, j = w; i >= 0; --i) // Fixme: i = n-1 and i >= 0
    if (p[i][j]) {
      // output the goods in the store
      j -= weight[i];
    }
}
