 #include <iostream>
 #include <unordered_map>
 
 using namespace std;
 
bool IsEqualTripuleSubSum(int arr[], int len) {
	if (arr == NULL || len == 0)
		return false;

	int* subSum = new int[len];
	if (subSum == NULL)
		return false;

	unordered_map<int, int> hmap;
	subSum[0] = arr[0];
	hmap.insert(make_pair(arr[0], 0));
	for (int idx = 1; idx < len; ++idx) {
		subSum[idx] = subSum[idx - 1] + arr[idx];
		hmap.insert(make_pair(subSum[idx], idx));
	}

	int curSum = 0;
	unordered_map<int, int>::const_iterator itor;
	for (int idx = len - 1; idx > 0; --idx) {
		curSum += arr[idx];

		itor = hmap.find(curSum);
		if (itor != hmap.end() &&
			(subSum[idx-1] - subSum[itor->second] == curSum))
			return true;
	}

	return false;
}
 int main() {
     int arr[] = {-1, 3, 2, 1, 1, -2, 2};
 
 
 }
