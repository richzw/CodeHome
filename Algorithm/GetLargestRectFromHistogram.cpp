/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.

Given height = [2,1,5,6,2,3],
return 10.
*/

// O(n^2)
int get_largest_rect_bruteforce(vector<int> vec){
	int max_area = 0;
	int len = vec.size();

	for (int i = 0; i < len; ++i){
		int min_height = vec[i];
		for (int j = i; j < len; ++j){
			min_height = min(min_height, vec[j]);
			int cur_area = min_height*(j - i + 1);//Fix me: +1
			if (cur_area > max_area)
				max_area = cur_area;
		}
	}

	return max_area;
}

// stack method ... good idea.
int get_largest_rect(vector<int> vec){
	stack<int> st;
	int len = vec.size();
	int max_area = 0;

	for (int i = 0; i < len; ++i){
		if (st.empty() || vec[i] > vec[st.top()]){
			st.push(i);
		}else{
			int index = st.top();
			st.pop();
			max_area = max(max_area, vec[index]*(st.empty()? i: i-st.top()-1)); //Fix me: -1
		}
	}

	return max_area;
}

// RMQ solution
int maxVal(int x, int y, int z) {
	return max( max(x, y), z);
}

int minVal(int* hist, int i, int j) {
	// check the range of i and j
	if (i == -1) return j;
	if (j == -1) return i;
	return (hist[i] < hist[j]) ? i : j;
}

int midVal(int s, int e) {
	return s + (e - s) / 2;
}

int constructSTUtil(int hist[], int ss, int se, int* st, int si) {
	if (ss == se)
		return st[si] = ss;

	int mid = midVal(ss, se);
	st[si] = minVal(hist, constructSTUtil(hist, ss, mid, st, si*2 + 1),
				constructSTUtil(hist, mid+1, se, st, si*2 + 2));

	return st[si];
}

int* constructST(int hist[], int n) {
	int hi = (int)ceil(log2(n));
	int max_size = 2 * (int)pow(2, hi) - 1;
	int* st = new int[max_size];

	constructSTUtil(hist, 0, n - 1, st, 0);

	return st;
}

int RMQUtil(int* hist, int* st, int ss, int se, int qs, int qe, int idx) {
	if (qs <= ss && se <= qe)
		return st[idx];

	if (se < qs || ss > qe)
		return -1;

	int mid = midVal(ss, se);
	return minVal(hist, RMQUtil(hist, st, ss, mid, qs, qe, 2*idx + 1),
			    RMQUtil(hist, st, mid+1, se, qs, qe, 2*idx + 2));
}


int RMQ(int* hist, int* st, int n, int qs, int qe) {
	if (qs < 0 || qe > n - 1 || qs > qe)
		return -1;

	return RMQUtil(hist, st, 0, n-1, qs, qe, 0);
}

int getMaxAreaRect(int* hist, int* st, int n, int l, int r) {
	if (l > r) return INT_MIN;
	if (l == r) return hist[l];

	int m = RMQ(hist, st, n, l, r);

	return maxVal(getMaxAreaRect(hist, st, n, l, m- 1),
			getMaxAreaRect(hist, st, n, m + 1, r),
			(r-l+1)*hist[m]);
}

int getMaxArea(int hist[], int n) {
	int* st = constructST(hist, n);

	return getMaxAreaRect(hist, st, n, 0, n - 1);
}

