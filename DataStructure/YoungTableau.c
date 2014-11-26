// search element in Yang tableau
// a[i][j]<a[i+1][j] and a[i][j]<a[i][j+1]
int findValueInYangTableau(int* matrix, int row, int col, int target){
	int i = 0;
	int j = col-1;

	while (i < row && j >= 0){
		if (target > *((matrix + i*row) + j))
			i++;
		else if (target < *((matrix + i*row) + j))
			j--;
		else
			return target;
	}

	return -1; // not find 
}

/*
令Aij为矩阵的中间元素，按照这个元素将矩阵划为4份，如果num大于Aij，则num可能落在左下、右上、右下三个子矩阵，对它们分别求子问题。
小于时也是类似的讨论。每次都会求三次子问题，每个子问题元素个数是上次的1/4，所以复杂度是f(N)=3f(N/4)+c，其中N=m*n是元素个数，c是大于0的常量，
主方法可求复杂度为O(N^(log4为底3))，计算器大概算了一下log4为底3约等于0.8。所以复杂度为O((m*n)^0.8)
*/
bool quadPart(int mat[][N] , int key , int l , int u , int r , int d , int &row , int &col)
{
	if(l > r || u > d)
		return false;
	if(key < mat[u][l] || key > mat[d][r])
		return false;
	int mid_col = (l+r)>>1;
	int mid_row = (u+d)>>1;
	if(mat[mid_row][mid_col] == key)     //查找成功
	{
		row = mid_row;
		col = mid_col;
		return true;
	}
	else if(l == r && u == d)
		return false;

	if(mat[mid_row][mid_col] > key)
	{   // 分别在右上角、左上角、左下角中查找
		return quadPart(mat , key , mid_col+1 , u , r , mid_row , row , col) ||
		       quadPart(mat , key , l , mid_row+1 , mid_col , d , row , col) ||
			   quadPart(mat , key , l , u , mid_col , mid_row , row , col) ;
	}
	else
	{   // 分别在右上角、左下角、右下角中查找
		return quadPart(mat , key , mid_col+1 , u , r , mid_row , row , col) ||
		       quadPart(mat , key , l , mid_row+1 , mid_col , d , row , col) ||
			   quadPart(mat , key , mid_col+1 , mid_row+1 , r , d , row , col) ;
	}
}

bool quadPart(int mat[][N] , int key , int &row , int &col)
{
	return quadPart(mat , key , 0 , 0 , N-1 , N-1 , row , col);
}


////////////////////////////////////////////////////////////////////////
void output_result(int elem, int row, int column){
    cout << "The elem " << elem << " is found " <<
            "and the row is " << row <<
            " and the column is " << column << endl;
}
void binary_search_row(int matrix[][4], int row, int column, int elem){
    if (matrix == NULL || row < 0 || column < 0)
        return ;
    int col = 0;
    if (matrix[row][col] == elem)
        return output_result(elem, row, col);
    else if (matrix[row][column] == elem)
        return output_result(elem, row, column);
    int mid = col + (column - col)/2;
    while (mid < column && mid > 0){
        if (matrix[row][mid] == elem)
            return output_result(elem, row, mid);
        else if (matrix[row][mid] > elem){
            column = mid;
        }else
            col = mid;
        mid = col + (column - col)/2;
    }
}
void binary_search_column(int matrix[][4], int row, int maxrow, int elem){
    if (matrix == NULL || row < 0 || maxrow < 0)
        return ;
    if (matrix[row][0] == elem)
        return output_result(elem, row, 0);
    else if (matrix[maxrow][0] == elem)
        return output_result(elem, maxrow, 0);
    int mid = row + (maxrow - row)/2;
    while (mid < maxrow && mid > 0){
        if (matrix[mid][0] == elem)
            return output_result(elem, mid, 0);
        else if (matrix[mid][0] > elem){
            maxrow = mid;
        }else
            row = mid;
        mid = row + (maxrow - row)/2;
    }
}

void findElemFromMatrix(int matrix[][4], int row, int column, int elem)
{
    if (matrix == NULL || row <= 0 || column <= 0)
            return ;

    int top_right_row = 0;
    int top_right_col = column - 1;

    // Socialite Problem
    // Check the top right corner element matrix[i][j]
    //       if matrix[i][j] > elem, delete the whole j column,
    //       otherwise, delete the whole i row.
    while ((top_right_row <= (row - 1)) && (top_right_col >= 0)){
        if (matrix[top_right_row][top_right_col] == elem ){
            return output_result(elem, top_right_row, top_right_col);
        }else if (matrix[top_right_row][top_right_col] < elem){
            ++top_right_row;
        }else{
            --top_right_col;
        }
    }

    // In case the last row,
    // Binary search to find the elem
    if (top_right_row == row - 1){
        return binary_search_row(matrix, row - 1, top_right_col, elem);
    }

    // In case the last column
    // Binary search to find the elem
    if (top_right_col == 0){
        return binary_search_column(matrix, top_right_row, row - 1, elem);
    }

    cout << "The elem " << elem << " is not in this matrix" <<endl;
    return ;
}

int main() {
    int matrix[4][4] = {{10, 30, 50, 51},
                        {20, 40, 60, 61},
                        {35, 42, 67, 70},
                        {36, 45, 75, 80}};

    findElemFromMatrix(matrix, 4, 4, 67);
    findElemFromMatrix(matrix, 4, 4, 35);
    findElemFromMatrix(matrix, 4, 4, 75);


    return 0;
}
