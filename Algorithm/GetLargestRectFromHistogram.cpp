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
			i--;
		}
	}

	return max_area;
}
