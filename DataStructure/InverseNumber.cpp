const int LEN = 6;
unsigned int tree[LEN] = {0};

unsigned int bit_read(int idx){
	unsigned int sum = 0;
	while (idx > 0){
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void bit_update(int idx, unsigned int val){
	while (idx <= LEN){ // bug: idx == 0
		tree[idx] += val;
		idx += (idx & -idx);
	}
}

int inverse_by_bit(vector<int>& arr){
	vector<int> tmp(arr.begin(), arr.end());

	sort(tmp.begin(), tmp.end());
	for (int i = 0; i < tmp.size(); ++i){
		int rank = int(lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin()+1);
		arr[i] = rank;
	}

	int cnt = 0;
	for (int i = arr.size()-1; i >= 0; --i){
		cnt += bit_read(arr[i] - 1);
		bit_update(arr[i], 1);
	}

	return cnt;
}
