Q: Find all contiguous subsequence in a given array of integers, whose sum falls in the given range.
===========

Starting from this problem: **find all contigous sub-sequence that has sum equals to x , so what we need is something similar.**

For every index ith, we can calculate the sum of the segment from 0 to ith, which is x, so, the problem now is we need to find from 0 to i - 1, 
how many segment has sum from (x - low) to (x - high), and it should be faster than O(n). 
So there are several data structures help you to do that in O(logn), which are Fenwick tree or Interval tree (a.k.a Segment tree).

So what we need to do is:

- Iterating through all index from 0 to n (n is the size of the array).
- At index ith, calculate, starting from 0 to ith index, the sum x, query the tree to get the total occurrences of numbers fall in the range (x - high, x - low).
- Add x to the tree.

So the time complexity will be O(n log n)
