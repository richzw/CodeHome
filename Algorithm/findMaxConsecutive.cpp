/*
  Q: To an array of integers is found that contains the maximum number of consecutive subset, 
     such as: 15, 7, 12, 6, 14, 13, 9, 11, returns: 5:[11, 12, 13, 14, 15]. 
     The easiest method is to sort and then scan again, but the complexity is O(nlgn), 
     Is there any O(n) method.
*/

// Hint: 1. hash map
//       2. union-find set

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
