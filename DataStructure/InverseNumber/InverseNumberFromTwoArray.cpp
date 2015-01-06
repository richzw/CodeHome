/*
3 // size of the array
1 2 3
3 2 1
output: 1 

7
1 1 2 3 2 3 4
4 3 3 2 2 1 1

output: 8
*/

// BIT method
unsigned int get_inverse_number(const vector<int>& a, const vector<int>& b){
	vector<int> tmp(a.begin(), a.end());
	for (vector<int>::const_iterator itor = b.begin(); itor != b.end(); ++itor)//(int val: b)
		tmp.push_back(*itor);

	sort(tmp.begin(), tmp.end());

	vector<int> tree(2*a.size() + 1);

	int cnt = 0;
	for (int idx = a.size()-1; idx >= 0; --idx){
		for (int v = lower_bound(begin(tmp), end(tmp), b[idx]) - begin(tmp);
			v;
			v -= v & (-v))
			cnt += tree[v];

		for (int w = lower_bound(tmp.begin(), tmp.end(), a[idx]) - tmp.begin() + 1; 
			w <= 2*a.size(); 
			w += w & (-w))
			tree[w]++;
	}

	return cnt;
}
