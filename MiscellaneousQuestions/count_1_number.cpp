/*
Counting the total numbers of 1 in the binary digit and all other numbers less than itself.
f(1)  = 1
f(10) = 10
f(11) = 100
…
What is f(n) ?
 
Analysis:  by different bit
    n (binary)                     f(n) (decimal sum by column)                  
       0  1                                               0 1                               
       1  0                                               1 1    1 =  2^(2-2)       {2 is the bits of n}                             
       1  1                                               2 2                                
    1  0  0                                             1 2 2    2 = 2^(3-2)                               
    1  0  1                                             2 2 3                                     
    1  1  0                                             3 3 3
    1  1  1                                             4 4 4
  1 0  0  0                                           1 4 4 4    4 = 2^(4-2)
  1 0  0  1                                           2 4 4 5
  1 0  1  0                                           3 4 5 5
  1 0  1  1                                           4 4 6 6
  1 1  0  0                                           5 5 6 6
  1 1  0  1                                           6 6 6 7
  1 1  1  0                                           7 7 7 7
  1 1  1  1                                           8 8 8 8
1 0 0  0  0                                           1 8 8 8 8     8 = 2^(5-2)      {5 is the bits of n}
Deduction: 
For high bit is 1 and the other bits are 0, the numbers of 1 is equal to 1 + (m-1)*(2^(m-2)), m is the bits of n. 
And the high bit is ascending order from 1, thus the numbers of 1 in the high bit is (n mod 2^m).

We can get the formula f(N) = f(N mod 2^m) + 1 + (N mod 2^m) + (m-1)*2^(m-2).
                       f(1) = 1 


*/
