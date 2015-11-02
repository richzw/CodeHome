
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
