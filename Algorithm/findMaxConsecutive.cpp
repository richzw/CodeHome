/*
  Q: To an array of integers is found that contains the maximum number of consecutive subset, 
     such as: 15, 7, 12, 6, 14, 13, 9, 11, returns: 5:[11, 12, 13, 14, 15]. 
     The easiest method is to sort and then scan again, but the complexity is O(nlgn), 
     Is there any O(n) method.
*/

// Hint: 1. hash map
//       2. 哈希 + 并查集： 哈希存储 每个元素的(key,index) ; 每个元素都是一个并查集(make_set(x))，
//        扫描序列，Union(key-1,key) , Union(key,key+1);
//        合并前通过哈希表查找到key-1,key+1的位置（index）, 需要 O(1) hashmap.
//       3. http://www.cppblog.com/everyday/articles/201439.html
//       4. bitmap, 初始为0，如果出现设置为1，找到连续最多的1即可。 

// here is hash map
int findMaxConsecutive(int arr[], int len){
	if (arr == NULL || len <= 0)
		return 0;

	// construct the hash map according to the array
	unordered_map<int, int> hash_arr;
	for (int index = 0; index < len; ++index){
		hash_arr[arr[index]] = arr[index];
	}

	int max_count = 0;
	unordered_map<int, int>::iterator find_itor;
	// mark the visited element as negative, limit for positive elements
	for (auto it = hash_arr.begin(); it != hash_arr.end(); ++it){
		if (it->second < 0)
			continue;
		
		int count = 1;
		int elem_low = it->first;
		int elem_high = it->first;
		while ((find_itor = hash_arr.find(elem_low - 1)) != hash_arr.end()){
			++count;
			find_itor->second = -find_itor->second;
			--elem_low;
		}
			
		while ((find_itor = hash_arr.find(elem_high + 1)) != hash_arr.end()){
			++count;
			find_itor->second = -find_itor->second;
			++elem_high;
		}
			
		if (count > max_count)
			max_count = count;

		// mark the visited element
		it->second = -it->second;
	}
	
	return max_count;
}

// here is union-find
int father[20] = {0};
int rank[20] = {0};

void make_set(int len){
    for (int index = 0; index < len; ++index){
        father[index] = index;
        rank[index] = 0;
    }
}

int find_set(int val){
    if (val != father[val]){
        rank[father[val]] += rank[val];
        father[val] = find_set(father[val]);
    }
    return father[val];
}

void union_set(int x, int y){
    	x = find_set(x);
	y = find_set(y);
	if (x == y)
		return;
	if (rank[x] > rank[y]){
		father[y] = x;
		rank[x] += rank[y];
	}else{
		if (rank[x] == rank[y]){
			rank[y]++;
		}else
			rank[y] += rank[x];
		father[x] = y;
	}
}

//here is another hash map
/*
用一个map<int, int>，它的key是一个起始的数字，value是这个起始数字起连续的个数。这样这个数组遍历一遍下来，
只要map维护好了，自然就能得到最长的连续子串了，并且算法复杂度应该是O(n)。（不考虑map函数实现的复杂度）

那么怎么来维护这个map呢？
1取出当前的整数，在map里看一下是否已经存在，若存在则直接取下一个，不存在转2 (为什么要看是否已经存在，因为题目没有说不会有重复的数字。)
2查看下map里面当前数字的前一个是否存在，如果存在，当前的最长长度就是前一个最长长度+1
3查看下map里面当前数字的后一个是否存在，如果存在，那么就将以下一个数字开始的子串的最后一个更新下，
    因为本来没有连上的2个子串，因为当前数字的出现连起来了
4接着再看下前面数字是否存在，如果存在，就更新以这个数字结尾的子串的第一个数字的连续子串长度，原因同上
*/
     map<int, int> mapping;
     int max = 0;
     // The start point for the longest chain
     int start = 0;
 
     for (int i=0; i<size; i++) {
         if (mapping.find(list[i]) == mapping.end()) {
             int cur = list[i];
             // Set current position as the start point for this potential longest chain
             int cur_start = cur;
             mapping.insert(make_pair(cur, 1));
 
             map<int, int>::iterator prev = mapping.find(cur - 1);
             map<int, int>::iterator next = mapping.find(cur + 1);
 
             if (prev != mapping.end()) {
                 // If previous number exists, increase current consecutive count
                 mapping[cur] = prev->second + 1;
             }
 
             if (next != mapping.end()) {
                 // Update the last one in the chain with the consecutive count from the one before current position
                 int last = next->first + next->second - 1;
                 mapping[last] = mapping[cur] = mapping[cur] + mapping[last];
             }
 
             if (prev != mapping.end()) {
                 // Update the first one in the chain with the consecutive count from the one after current position
                 int first = prev->first - prev->second + 1;
                 mapping[first] = mapping[cur];
 
                 // Use the first one as the start point for the whole chain
                 cur_start = first;
             }
 
             if (mapping[cur_start] > max) {
                 start = cur_start;
                 max = mapping[cur_start];
             }
         }
     }
