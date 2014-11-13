//http://www.geeksforgeeks.org/suffix-array-set-1-introduction/
// build suffix array

struct suffix{
	int index;
	char* suff;
};

int cmp(struct suffix a, struct suffix b){
	return strcmp(a.suff, b.suff)< 0? 1:0;
}

int* buildSuffixArray(char* txt, int n) {
	struct suffix suffixes[n];

	// store suffixes and their indexes in an array of structure
	for (int i = 0; i < n; i++){
		suffixes[i].index = i;
		suffixes[i].suff = txt+i;
	}

	// sort the suffixes 
	sort(suffixes, suffixes+n, cmp);

	int* suffixArr = new int[n];
	for (int i = 0; i < n; ++i)
		suffixArr[i] = suffixes[i].index;

	return suffixArr;
}

void search(char* pat, char* txt, int* suffixArr, int n){
	int m = strlen(pat);

	int l = 0, r = n -1;
	while (l <= r){
		int mid = l + (r-l)/2;
		int res = strncmp(pat, txt+suffixArr[mid], m);

		if (res == 0){
			cout << "Pattern found at index" << suffixArr[mid];
			return;
		}

		if (res < 0)
			r = mid - 1;
		else
			l = mid + 1;
	}

	cout << "Pattern Not Found";
}
