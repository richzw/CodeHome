

[R](https://en.wikipedia.org/wiki/Timsort)

[Adaptive Mergesort](http://www.drmaciver.com/2010/01/understanding-timsort-1adaptive-mergesort/)

[Timsort algorithm](http://www.infopulse.com/blog/timsort-sorting-algorithm/)
 
 The thing is that in reality Timsort is not a standalone algorithm but a hybrid, an efficient combination of a number of other algorithms, seasoned with the author’s ideas. The mechanism of the algorithm can be briefly explained as follows:

- A particular algorithm is used to split the input array into sub-arrays.
- Each sub-array is sorted with a simple Insertion Sort.
- The sorted sub-arrays are merged into one array with the use of Merge Sort. As usual, the devil hides in the details, namely, in the algorithm in p. 1 and the merge sort modification in p. 3.

Definition:

- **N**: the length of the input array
- **run**: an ordered sub-array in the input array. At the same time, the order is non-descending or strictly descending, i.e. “a0 ≤ a1 ≤ a2 ≤ …» or «a0 > a1 > a2 > …”
- **minrun**: as it was said above, in the first step of the algorithm, the input array is split into runs. minrun is a minimum length of such run. This number is calculated by a certain logics from the N number.



