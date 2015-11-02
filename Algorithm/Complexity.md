
Time complexity of algorithm
------------

The most common metric for calculating time complexity is Big O notation. This removes all constant factors so that 
the running time can be estimated in relation to N as N approaches infinity. In general you can think of it like this:

`statement;`

Is **constant**. The running time of the statement will not change in relation to N.

```c
for ( i = 0; i < N; i++ )
     statement;
```

Is **linear**. The running time of the loop is directly proportional to N. When N doubles, so does the running time.

```c
for ( i = 0; i < N; i++ ) {
  for ( j = 0; j < N; j++ )
    statement;
}
```

Is **quadratic**. The running time of the two loops is proportional to the square of N. When N doubles, 
the running time increases by N * N.

```c
while ( low <= high ) {
  mid = ( low + high ) / 2;
  if ( target < list[mid] )
    high = mid - 1;
  else if ( target > list[mid] )
    low = mid + 1;
  else break;
}
```

Is **logarithmic**. The running time of the algorithm is proportional to the number of times N can be divided by 2.
This is because the algorithm divides the working area in half with each iteration.

```c
void quicksort ( int list[], int left, int right )
{
  int pivot = partition ( list, left, right );
  quicksort ( list, left, pivot - 1 );
  quicksort ( list, pivot + 1, right );
}
```

Is **N * log ( N )**. The running time consists of N loops (iterative or recursive) that are logarithmic, 
thus the algorithm is a combination of linear and logarithmic.

----------

**Time complexity of loop**

- **O(n)**: Time Complexity of a loop is considered as _O(n)_ if the loop variables is incremented / decremented by a constant amount. For example following functions have _O(n)_ time complexity.

```c
   // Here c is a positive integer constant   
   for (int i = 1; i <= n; i += c) {  
        // some O(1) expressions
   }

   for (int i = n; i > 0; i -= c) {
        // some O(1) expressions
   }
```   
 
- **O(n^c)**: Time complexity of nested loops is equal to the number of times the innermost statement is executed. For example the following sample loops have _O(n^2)_ time complexity

 ``` 
   for (int i = 1; i <=n; i += c) {
       for (int j = 1; j <=n; j += c) {
          // some O(1) expressions
       }
   }

   for (int i = n; i > 0; i += c) {
       for (int j = i+1; j <=n; j += c) {
          // some O(1) expressions
   }
 ```

For example Selection sort and Insertion Sort have O(n^2) time complexity.

 
- **O(Logn)** Time Complexity of a loop is considered as _O(Logn)_ if the loop variables is divided / multiplied by a constant amount.

```
   for (int i = 1; i <=n; i *= c) {
       // some O(1) expressions
   }
   for (int i = n; i > 0; i /= c) {
       // some O(1) expressions
   }
```

For example Binary Search(refer iterative implementation) has O(Logn) time complexity.

 
- **O(LogLogn)** Time Complexity of a loop is considered as _O(LogLogn)_ if the loop variables is reduced / increased exponentially by a constant amount.

```
   // Here c is a constant greater than 1   
   for (int i = 2; i <=n; i = pow(i, c)) { 
       // some O(1) expressions
   }
   //Here fun is sqrt or cuberoot or any other constant root
   for (int i = n; i > 0; i = fun(i)) { 
       // some O(1) expressions
   }
```   
   
See this for more explanation.

- **O(n^(1/2))**

```
void fun(int n)
{
   int j = 1, i = 0;
   while (i < n)
   {
       // Some O(1) task
       i = i + j;
       j++;
   }
}
```

The loop variable `i` is incremented by 1, 2, 3, 4, … until i becomes greater than or equal to n.

The value of i is x(x+1)/2 after x iterations. So if loop runs x times, then x(x+1)/2 < n. Therefore time complexity can be written as Θ(√n). 

- ps

```
int fun(int n)
{    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < n; j += i)
        {
            // Some O(1) task
        }
    }    
}
```

**Analysis**:

For i = 1, the inner loop is executed n times.
For i = 2, the inner loop is executed approximately n/2 times.
For i = 3, the inner loop is executed approximately n/3 times.
For i = 4, the inner loop is executed approximately n/4 times.
…………………………………………………….
For i = n, the inner loop is executed approximately n/n times.

So the total time complexity of the above algorithm is (n + n/2 + n/3 + … + n/n), Which becomes n * (1/1 + 1/2 + 1/3 + … + 1/n)

The important thing about series (1/1 + 1/2 + 1/3 + … + 1/n) is, it is equal to Θ(Logn). So the time complexity of the above code is Θ(nLogn).

------

Ref:

[1](http://stackoverflow.com/questions/11032015/how-to-find-time-complexity-of-an-algorithm)
[2](http://www.geeksforgeeks.org/analysis-of-algorithms-set-4-analysis-of-loops/)
[3](http://www.geeksforgeeks.org/time-complexity-where-loop-variable-is-incremented-by-1-2-3-4/)
[4](http://www.geeksforgeeks.org/interesting-time-complexity-question/)
