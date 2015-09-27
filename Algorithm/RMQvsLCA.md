
[Ref](https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/#Lowest%20Common%20Ancestor%20(LCA))

**RMQ** vs **LCA**

------------------

Range Minimum Query(RMQ)

Given an array A[0, N-1] find the position of  the element with the minimum value between two given indices.

Solutions:

- An <O(N), O(sqrt(N))> solution

An interesting idea is to split the vector in sqrt(N) pieces. We will keep in a vector M[0, sqrt(N)-1] the position 
for the minimum value for each section. M can be easily preprocessed in O(N).

- Sparse Table

A better approach is to preprocess RMQ for sub arrays of length 2k using dynamic programming. We will 
keep an array M[0, N-1][0, logN] where M[i][j] is the index of the minimum value in the sub array starting at i having length 2j.

- Segment Tree

For solving the RMQ problem we can also use segment trees. A segment tree is a heap-like data structure that can be used
for making update/query operations upon array intervals in logarithmical time. We define the segment tree for the interval [i, j] in the following recursive manner:

  - the first node will hold the information for the interval [i, j]
  - if i<j the left and right son will hold the information for the intervals [i, (i+j)/2] and [(i+j)/2+1, j]

- Cartesian Tree (reduce RMQ to LCA)

A Cartesian Tree of an array A[0, N - 1] is a binary tree C(A)  whose root is a minimum element of A, 
labeled with the position i of this minimum. The left child of the root is the Cartesian Tree of A[0, i - 1] if i > 0, 
otherwise there’s no child. The right child is defined similary for A[i + 1, N - 1]. 
Note that the Cartesian Tree is not necessarily unique if A contains equal elements. 
In this tutorial the first appearance of the minimum value will be used, thus the Cartesian Tree will be unique.  
It’s easy to see now that RMQA(i, j) = LCAC(i, j).


**LCA**

- Eular Tour (reduce LCA to RMQ)

On an input tree T, we build 3 arrays.

- Euler[1,..,2n-1] – The nodes visited in an Euler tour of T. Euler[i] is the label of the i-th node visited in the tour.

- Level[1,..2n-1] – The level of the nodes we got in the tour. Level[i]  is the level of node Euler[i].
	(level is defined to be the distance from the root)

- Representative[1,..n] – Representative[i] will hold the index of the first occurrence of node i in Euler[].


