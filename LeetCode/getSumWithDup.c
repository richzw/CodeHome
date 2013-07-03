/*
Given a target number, and a series of candidate numbers, print out all combinations, 
so that the sum of candidate numbers equals to the target.

Here order is not important, so don’t print the duplicated combination.

e.g. target is 7, candidate is 2,3,6,7
output should be 7 and 3+2+2 (but not print 2+3+2, 2+2+3)
*/

void print_result(int candidates[], int indexes[], int cnt){
  	for (int i = 1; i <= cnt; ++i){
		cout << candidates[indexes[i]] << " + ";
	}
	cout << endl;
}
void solve_combine_helper(int target, int sum, int candidates[], int count, int indexes[], int i){
	if (sum > target)
		return;
	if (sum == target)
		print_result(candidates, indexes, i);

	for (int j = indexes[i]; j < count; ++j){
		indexes[i + 1] = j;
		solve_combine_helper(target, sum+candidates[j], candidates, count, indexes, i+1);
	}
}
void solve_combine(int target, int candidates[], int count){
	int indexes[100] = {0};
	int sum = 0;
	solve_combine_helper(target, sum, candidates, count, indexes, 0);
}
