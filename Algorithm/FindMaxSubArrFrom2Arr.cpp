
typedef pair<int, int> int_pair;

int findMaxSubArray(int a[], int b[], int len){
	int j = 0;
	int* pc = new int[len];
	int* psum = new int[len];
	hash_map<int, int> sum_map;
	hash_map<int, int>::const_iterator itor;

	for (int i = 0; i < len; ++i){
		pc[i] = a[i] - b[i];
	}

	psum[0] = pc[0];
	for (int i = 0; i < len - 1; ++i){
		psum[i+1] = psum[i] + pc[i+1];
		itor = sum_map.find(i);
		if (itor == sum_map.end()){
			sum_map.insert(int_pair(psum[i], i));
		} else{
			j = itor->second;
			return j;
		}
	}

	return 0;
}

int main(){
	int a[] = {1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0};
	int b[] = {0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1};
	int len = sizeof(a)/sizeof(a[0]);

	findMaxSubArray(a, b, len);
}
