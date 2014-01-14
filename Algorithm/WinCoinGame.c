/*
There are n coins in a line. (Assume n is even). 
Two players take turns to take a coin from one of the ends of the line until there are no more coins left.
The player with the larger amount of money wins.
*/
//P(i, j) = max { P1, P2 }
//        = max { Ai + min { P(i+2, j),   P(i+1, j-1) },
//                Aj + min { P(i+1, j-1), P(i,   j-2) } }

#define MAX_N 6
int max_money(int a[], int n){
	int p[MAX_N][MAX_N] = {0};
	int aa, b, c;

	for (int i = 0; i < n; ++i){
		for (int j = 0, k = i; k < n; j++, k++){
			aa = ((j+2 <= n-1)            ? p[j+2][k] : 0);
			b = ((j+1 <= n-1 && k-1 >= 0) ? p[j+1][k-1] : 0);
			c = ((k-2 >= 0)               ? p[j][k-2] : 0);
			p[j][k] = max(a[j] + min(aa,b), a[k] + min(b,c));
		}
	}

	return p[0][n-1];
}

int _tmain(int argc, _TCHAR* argv[])
{
	int coin_arr[] = { 3, 2, 2, 3, 1, 2 };
	cout << max_money(coin_arr, sizeof(coin_arr)/sizeof(coin_arr[0])) << endl;
  return 0;
}
