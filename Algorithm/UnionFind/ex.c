/*
Q1:  Union-find with specific canonical element. 
Add a method find() to the union-find data type so that find(i) returns the largest element 
in the connected component containing i. The operations, union(), connected(), and find() should all take logarithmic time 
or better.

For example, if one of the connected components is {1,2,6,9}, then the find() method should return 9 for each of 
the four elements in the connected components.
*/
//Hint: maintain an extra array to the weighted quick-union data structure that stores for each root i the large element 
//in the connected component containing i


/*
Successor with delete. Given a set of N integers S={0,1,...,N−1} and a sequence of requests of the following form:
    Remove x from S
    Find the successor of x: the smallest y in S such that y≥x.

design a data type so that all operations (except construction) should take logarithmic time or better.
*/
//hint:  use the modification of the union-find data discussed in the previous question

//Assume we already have successors kept in a tree-like data structure, with root[i] pointing to the successor of i. 
//The key observation here is that removing a number x from the set is quite analogous to joining two union-find sets: 
//we only need to change root[x] to root[x + 1]. Note that this will also change successors of numbers whose successors 
//were x. After that, the invariance that root[i] points to the successor of i still holds.

//We cannot direct apply weight quick union here, because it may changes root[x + 1] to root[x], 
//possibly making successor of x + 1 a number smaller than x + 1. But we can exploit path compression, 
//and make worst case time complexity within O(N + M log N).
