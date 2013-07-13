/*
Q: 股市上一个股票的价格从开市开始是不停的变化的，需要开发一个系统，
   给定一个股票，它能实时显示从开市到当前时间的这个股票的价格的中位数（中值）
*/

/*
A: 
1. 若用一个数组线性存储，则Insert为O(1)，Median用selection算法，为O(n)
2. 若用顺序统计数存储，则Insert为O(logn)，Median为O(logn)
3. 若用双堆存储，一个大根堆，一个小根堆，则Inert为O(logn)，Median为O(1)
*/

double heap, left_max_heap and right_min_heap.
left_max_hep < medium < right_min_heap

void insert(heap<int> left_max_heap, int value, heap<int> right_min_heap){
 	if (value < medium)
    	left_max_heap.insert(value);
    else 
    	right_min_heap.insert(value);
    	
    if (left_max_heap.size() < right_min_heap.size()){
    	left_max_heap.insert(medium);
    	medium = right_min_heap.top();
    	right_min_heap.pop();
    }
    else if (left_max_heap.size() > right_min_heap.size() + 1){
    	right_min_heap.insert(medium);
    	medium = left_max_heap.top();
    	left_max_heap.pop();
    }
}
