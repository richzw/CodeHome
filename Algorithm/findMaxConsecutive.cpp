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

//here is hash map
