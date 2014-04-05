// one dimensionality tree array
const int LEN = 10;
int oarr[LEN] = {0};

int lowbit(int t){  //except the parameter 0
	return t&(-t);
}
void update(int idx, int val){
	while (idx < LEN){
		oarr[idx] += val;
		idx += lowbit(idx);
	}
}
int sum_oarr(int n){
	int sum = 0;
	while (n > 0){
		sum += oarr[n];
		n -= lowbit(n);
	}

	return sum;
}

//
