
/*
Counting the total numbers of 1 in the binary digit and all other numbers less than itself.
f(1)  = 1
f(10) = 10
f(11) = 100
…
What is f(n) ?
 
Analysis:  by different bit
    n (binary)                     f(n) (decimal sum by column)                  
          0  1                                               0  1                               
          1  0                                               1  1                               
          1  1                                               2  2                                
       1  0  0                                             1 2  2                                
       1  0  1                                             2 2  3                                     
       1  1  0                                             3 3  3
       1  1  1                                             4 4  4
     1 0  0  0                                           1 4 4 4
     1 0  0  1                                           2 4 4 5
     1 0  1  0                                           3 4 5 5
     1 0  1  1                                           4 4 6 6


*/
