// Perfect Shuffle
1. Find a 2m=3**k - 1 such that 3**k <= 2n < 3**(k+1)
2. Do a right cyclic shift of A[m+1, ..., n+m] by a distance m
3. For each i is {0,1,.., k-1}, starting at 3**i, do the cycle leader algorithm 
   for the in-shuffle permutation of order 2m
4. Recursively do the in-shuffle algorithm on A[2m+1, ..., 2n]

void reverse(int* a, int from, int to){
	int t;
	for (; from < to; ++from, --to){
		t = a[from];
		a[from] = a[to];
		a[to] = t;
	}
}

void right_rotate(int* a, int num, int n){
	reverse(a, 1, n-num);
	reverse(a, n-num+1, n);
	reverse(a, 1, n);
}

void cycle_leader(int* a, int from, int mod){
	int t, i;
	
	for (i = from*2%mod; i != from; i = i*2%mod){
		t = a[i];
		a[i] = a[from];
		a[from] = t;
	}
}

void PerfectShuffle(int* a, int n){
	int n2, m, i, k, t;
	
	for (; n > 1; ){
		// step 1
		n2 = n*2;
		for (k=0, m=1; n2/m >= 3; ++k, m*= 3)
			;
		m/=2;
		
		// step 2
		right_rotate(a+m, m, n);
		
		// step 3
		for (i=0, t = 1; i < k; ++i, t*=3){
			cycle_leader(a, t, m*2+1);
		}
		
		// step 4
		a += m*2;
		n -= m;
	}
	
	// n = 1
	t = a[1];
	a[1] = a[2];
	a[2] = t;
}
