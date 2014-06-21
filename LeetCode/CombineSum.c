/*
Given a collection of candidate numbers (C) and a target number (T), 
find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used **once** in the combination.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
A solution set is: 
[1, 7] 
[1, 2, 5] 
[2, 6] 
[1, 1, 6] 
*/

bool compare(int a, int b){
	return a < b;
}

void combine_sum(int arr[], int len, int target){
	if (arr == NULL || len <= 0)
		return ;
	
	std::sort(arr, arr+len, compare);
	vector<int> elems;
	vector<vector<int> > result;
	
	return helper(arr, 0, len, target, elems, reslut);
}

void helper(int arr[], int begin, int len, int target, vector<int>& elems, vector<vector<int> >& result){
	if (target < 0 || begin >= len)
		return;
	
	if (target == 0){
		result.push_back(elems);
		return;
	}
	
	for (int idx = begin; idx < len; ++idx){
		if (idx > begin && arr[idx] == arr[idx-1])  // FixMe here
			continue;
		
		elems.push_back(arr[idx]);
		helper(arr, idx, len, target-arr[idx], elems, result);
		//helper(arr, idx+1, len, target-arr[idx], elems, result);
		elems.pop_back();
	}
}
