/*
 Q1: Given one matrix, each row are ascending ordered. each column is  ascending ordered.
     To find one element in this matrix.
     ex.      10  30 50
              20  40 80,    find 40 in this matrix.
*/

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
