/*
As we know, there is one `[Four color theorem]`(http://en.wikipedia.org/wiki/Four_color_theorem) related question, 
Given the number of country, then color the country map with no more 4 colors. 

What if we know the country map after colored with no more than 5 colors, and the same color as the adjacent grid indicates the same country, 
only for the up, down, left, right directions, not for oblique direction. How to get the country number from the map? 

Given the map
1，3，3，3
1，2，5，3
2，4，5，5
and the country number is 6.
*/
// flood-fill algorithm
void floodfill(int* matrix, int x, int y, int row, int col,  int val){
	if (x >= 0 && x < row && y >= 0 && y < col && *((matrix+x*col)+y) == val){
		*((matrix+x*col)+y) = -val;  // negative the value, mark as visit

		floodfill(matrix, x+1, y, row, col, val);
		floodfill(matrix, x-1, y, row, col, val);
		floodfill(matrix, x, y+1, row, col, val);
		floodfill(matrix, x, y-1, row, col, val);
	}
}

int find_country_number(int* matrix, int row, int col){
	if (matrix == NULL)
		return 0;

	int countries = 0;
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j){
			if (*((matrix+i*col)+j) > 0){ //
				floodfill(matrix, i, j, row, col, *((matrix+i*col)+j));
				++countries;
			}
		}

	return countries;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int matrix[][4] = {
		{1,3,3,3},
		{1,2,5,3},
		{2,4,5,5},
	};

	cout << "The number of country is that " << find_country_number((int*)matrix, 3, 4) << endl;
