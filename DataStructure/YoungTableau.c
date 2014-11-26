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
