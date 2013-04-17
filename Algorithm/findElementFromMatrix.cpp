/*
 Q1: Given one matrix, each row are ascending ordered. each column is  ascending ordered.
     To find one element in this matrix.
     ex.      10  30 50
              20  40 80,    find 40 in this matrix.
*/

void binary_search_row(){
}
void binary_search_column(){
}
void findElemFromMatrix(int matrix[][], int row, int column, int elem)
{
    if (matrix == NULL || row <= 0 || colum <= 0)
            return ;
    int top_right_row = 0;
    int top_right_col = column;
    // Socialite Problem
    // Check the top right corner element matrix[i][j]
    //       if matrix[i][j] > elem, delete the whole j column,
    //       otherwise, delete the whole i row.
    while ((top_right_row <= (row - 1)) && (top_right_col >= 0)){
        if (matrix[top_right_row][top_right_col] == elem ){
            cout << "The elem " << elem << " is found " <<
                    "and the row is " << top_right_row
                    " and the column is " << top_right_column << endl;
            return ;
        }else if (matrix[top_right_row][top_right_col] < elem){
            ++top_right_row;
        }else{
            --top_right_col;
        }
    }
    // In case the last row,
    // Binary search to find the elem
    if (top_right_row == row - 1){
        binary_search_row(matrix, top_right_col);
    }
    // In case the last column
    // Binary search to find the elem
    if (top_right_col == 0){
        binary_search_column(matrix, top_right_row);
    }
    return ;
 51 }
