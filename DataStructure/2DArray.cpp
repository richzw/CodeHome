// Two dimensional array

	int** ary = new int*[row];
	for (int r = 0; r < row; ++r)
		ary[r] = new int[column];

	vector<vector<int> > dyAry(row, vector<int>(column));
