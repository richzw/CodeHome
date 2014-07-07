/*
Q:  A disorganized carpenter has a mixed pile of N nuts and N bolts. The goal is to find the corresponding pairs of 
nuts and bolts. Each nut fits exactly one bolt and each bolt fits exactly one nut. By fitting a nut and a bolt together, 
the carpenter can see which one is bigger (but the carpenter cannot compare two nuts or two bolts directly).
Design an algorithm for the problem that uses NlogN compares (probabilistically).
*/

//Ref: http://www.wisdom.weizmann.ac.il/~naor/PUZZLES/nuts_solution.html
//Ref: http://courses.csail.mit.edu/6.046/spring03/handouts/ps2sol.pdf
/*
Let’s assume the nuts and bolts are provided to us in two arrays N[1 . . . n] and B[1 . . . n],
where we are allowed to compare elements across, but not within, these two arrays.
We use a divide-and-conquer algorithm very similar to randomized quicksort. The
algorithm ﬁrst performs a partition operation as follows: pick a random nut N[i].
Using this nut, rearrange the array of bolts into three groups of elements: ﬁrst the
bolts smaller than N[i], then the bolt that matches N[i], and ﬁnally the bolts larger
than N[i]. Next, using the bolt that matches N[i] we perform a similar partition
of the array of nuts. This pair of partitioning operations can easily implemented in
Θ(n) time, and it leaves the nuts and bolts nicely partitioned so that the “pivot” nut
and bolt are aligned with each-other and all other nuts and bolts are on the correct
side of these pivots — smaller nuts and bolts precede the pivots, and larger nuts and
bolts follow the pivots. Our algorithm then ﬁnishes by recursively applying itself to
the subarrays to the left and right of the pivot position to match these remaining
nuts and bolts. We can assume by induction on n that these recursive calls will properly match the remaining bolts.

*/

