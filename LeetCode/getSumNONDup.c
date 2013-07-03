/*
Candidate Set = {10, 1, 2, 7, 6, 1, 5}
Target Number = 8

One possible output could be:
1+1+6
1+2+5
1+7
2+6
*/

void solve_combine_non_dup_helper(int target, int sum, int candidates[], int count, int startId, vector<int> vec){
  if (sum > target)
		return;
	if (sum == target){
		for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
			cout << *iter << " + ";
		cout << endl;
		return;
	}
	
	for (int i = startId; i < count; ++i){
		vec.push_back(candidates[i]);
		solve_combine_non_dup_helper(target, sum+candidates[i], candidates, count, i+1, vec);
		vec.pop_back();

		while(candidates[i+1] == candidates[i])
			i++;
	}
}

void solve_combine_non_dup(int target, int candidates[], int count){
	vector<int> elem_vec;

	sort(candidates, candidates+count, func);
	solve_combine_non_dup_helper(target, 0, candidates, count, 0, elem_vec);
}
