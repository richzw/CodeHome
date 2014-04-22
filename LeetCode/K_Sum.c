/*
Triple sum:
Given an array and a value, find if there is a triplet in array whose sum is equal to the given value.
If there is such a triplet present in array, then print the triplet and return true. Else return false. 
For example, if the given array is {12, 3, 4, 1, 6, 9} and given sum is 24, then there is a triplet (12, 3 and 9) present in array whose sum is 24.
*/
// naive method, brute force, O(N^3)
bool find3Numbers(int arr[], int len, int sum){
	for (int i = 0; i < len - 2; ++i)
		for (int j = 0; j < len - 1; ++j)
			for (int k = 0; k < len; ++k)
				if (arr[i] + arr[j] + arr[k] == sum){
					printf("Triplet is %d, %d, %d", arr[i], arr[j], arr[k]);
					return true;
				}

	return false;
}

// sort method, O(N^2)
bool find3Number2_v1(int arr[], int len, int sum){
	int l, r;

	qsort(arr, len, sizeof(int), compare);

	for (int i = 0; i < len-1; ++i){
		// To find the other two elements, start two index variables
        // from two corners of the array and move them toward each other
		// convert to 2 sum
		l = i + 1;
		r = len - 1;
		while (l < r){
			if (arr[l] + arr[i] + arr[r] == sum){
				printf("Triplet is %d, %d, %d", arr[i], arr[l], arr[r]);
				return true;			
			}
			else if (arr[l] + arr[i] + arr[r] < sum)
				l++;
			else
				r--;
		}
	}

	return false;
}

//
vector<int> threeSum(vector<int> &num) {
    vector<int> vecResult;
    if(num.size() < 3)
        return vecResult;

    vector<int> vecTriple(3, 0);
    sort(num.begin(), num.end());

    int iCurrentValue = num[0];
    int iCount = num.size() - 2; // (1) trick 1
    for(int i = 0; i < iCount; ++i) {
        if(i && num[i] == iCurrentValue) { // (2) trick 2: trying to avoid repeating triples
            continue;
        }

        // do 2 sum
        vecTriple[0] = num[i];
        int j = i + 1;
        int k = num.size() - 1;
        while(j < k) {
            int iSum = num[j] + num[k];
            if(iSum + vecTriple[0] == 0) {
                vecTriple[1] = num[j];
                vecTriple[2] = num[k];
                vecResult.push_back(vecTriple); // copy constructor
                ++j;
                --k;
            }
            else if(iSum + vecTriple[0] < 0)
                ++j;
            else
               --k;

        }

        iCurrentValue = num[i];
    }
            // trick 3: indeed remove all repeated triplets
            // trick 4: already sorted, no need to sort the triplets at all, think about why?
    vector< vector<int> >::iterator it = std::unique(vecResult.begin(), vecResult.end());
    vecResult.resize( std::distance(vecResult.begin(), it) );

    return vecResult;
}

// 2 sum: better solution, hashMap
bool find2Numbers(int arr[], int len, int sum){
	set<int> hmap;

	for (int i = 0; i < len; ++i){
		hmap.insert(arr[i]);
	}

	for (int i = 0; i < len; ++i){
		if (hmap.find(sum-arr[i]) != hmap.end()){
			//got it... haha
			return true;
		}
	}

	return false;
} 
