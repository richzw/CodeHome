/*
 Q1: Given one matrix, each row are ascending ordered. each column is  ascending ordered.
     To find one element in this matrix.
     ex.      10  30 50
              20  40 80,    find 40 in this matrix.
*/

  5 void binary_search_row(){
  6
  7 }
  8
  9 void binary_search_column(){
 10
 11 }
 12
 13 void findElemFromMatrix(int matrix[][], int row, int column, int elem)
 14 {
 15     if (matrix == NULL || row <= 0 || colum <= 0)
 16             return ;
 17
 18     int top_right_row = 0;
 19     int top_right_col = column;
 20
 21     // Socialite Problem
 22     // Check the top right corner element matrix[i][j]
 23     //       if matrix[i][j] > elem, delete the whole j column,
 24     //       otherwise, delete the whole i row.
 25     while ((top_right_row <= (row - 1)) && (top_right_col >= 0)){
 26         if (matrix[top_right_row][top_right_col] == elem ){
 27             cout << "The elem " << elem << " is found " <<
 28                     "and the row is " << top_right_row
 29                     " and the column is " << top_right_column << endl;
 30             return ;
 31         }else if (matrix[top_right_row][top_right_col] < elem){
 32             ++top_right_row;
 33         }else{
 34             --top_right_col;
 35         }
 36     }
 37
 38     // In case the last row,
 39     // Binary search to find the elem
 40     if (top_right_row == row - 1){
 41         binary_search_row(matrix, top_right_col);
 42     }
 43
 44     // In case the last column
 45     // Binary search to find the elem
 46     if (top_right_col == 0){
 47         binary_search_column(matrix, top_right_row);
 48     }
 49
 50     return ;
 51 }
