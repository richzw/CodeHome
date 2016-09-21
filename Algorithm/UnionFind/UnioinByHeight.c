/*
 The idea is to always attach smaller depth tree under the root of the deeper tree. This technique is called union by rank. 
 The term rank is preferred instead of height because if path compression technique (we have discussed it below) is used, 
 then rank is not always equal to height. Also, size (in place of height) of trees can also be used as rank.
 
*/

const int UFARRLEN = 10;
int UFArr[UFARRLEN] = {0};

void UF_init() {
	for (int i = 0; i < UFARRLEN; ++i)
		UFArr[i] = i;
}

int UF_root(int i) {
	while (i != UFArr[i]) {
		UFArr[i] = UFArr[UFArr[i]]; // one line for path compression
		i = UFArr[i];
	}

	return i;
}

bool UF_find(int i, int j) {
	return UF_root(i) == UF_root(j);
}

void UF_union(int i, int j) {
	int ri = UF_root(i);
	int rj = UF_root(j);

	UFArr[ri] = rj;
}
