/*
Given an N*N matrix A, whose elements are either 0 or 1. A[i, j] means the number in the i-th row and j-th column. 
Initially we have A[i, j] = 0 (1 <= i, j <= N).
We can change the matrix in the following way. Given a rectangle whose upper-left corner is (x1, y1) 
and lower-right corner is (x2, y2), we change all the elements in the rectangle by using "not" operation 
(if it is a '0' then change it into '1' otherwise change it into '0'). To maintain the information of the matrix, 
you are asked to write a program to receive and execute two kinds of instructions.

1. C x1 y1 x2 y2 (1 <= x1 <= x2 <= n, 1 <= y1 <= y2 <= n) changes the matrix by using the rectangle 
  whose upper-left corner is (x1, y1) and lower-right corner is (x2, y2).
2. Q x y (1 <= x, y <= n) querys A[x, y]. 
*/

// solution: two dimemsionality tree array
