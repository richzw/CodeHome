/*
给定一个数组，数组中有n个元素。数组有这样一个特性：每个数的位置索引与排序后该数的位置索引小于k（k<<n）。
请问有没有时间复杂度低于nlogn的算法来对这个数组进行排序。

min-heap, time complexity O(nlogk)
*/

void specific_sort(vector<int> &vec, int k){
	priority_queue<int, vector<int>, greater<int> > heap;

	for (int idx = 0; idx < k; ++idx){
		heap.push(vec[idx]);
	}

	int index = 0; 
	while (index + k < vec.size()){
		vec[index++] = heap.top();
		heap.pop();
		heap.push(vec[index+k]);
	}

	while(heap.size() > 0){
		vec[index++] = heap.top();
		heap.pop();
	}
}
