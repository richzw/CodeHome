Q: **Find all contiguous subsequence in a given array of integers, whose sum falls in the given range.**

-------------------------

Starting from this problem: **find all contigous sub-sequence that has sum equals to x , so what we need is something similar.**

For every index ith, we can calculate the sum of the segment from 0 to ith, which is x, so, the problem now is we need to find from 0 to i - 1, 
how many segment has sum from (x - low) to (x - high), and it should be faster than O(n). 
So there are several data structures help you to do that in O(logn), which are Fenwick tree or Interval tree (a.k.a Segment tree).

So what we need to do is:

- Iterating through all index from 0 to n (n is the size of the array).
- At index ith, calculate, starting from 0 to ith index, the sum x, query the tree to get the total occurrences of numbers fall in the range (x - high, x - low).
- Add x to the tree.

So the time complexity will be O(n log n)

**Solution 1**
class Solution:
    def subarraySumII(self, A, start, end):
        """
        O(n lg n) Binary Search
        Bound:
        f[i] - f[j] = start
        f[i] - f[j'] = end
        start < end
        f[j] > f[j']
        :param A: an integer array
        :param start: start an integer
        :param end: end an integer
        :return:
        """
        n = len(A)
        cnt = 0
        f = [0 for _ in xrange(n+1)]

        for i in xrange(1, n+1):
            f[i] = f[i-1]+A[i-1]  # from left

        f.sort()
        for i in xrange(n+1):
            lo = bisect_left(f, f[i]-end, 0, i)
            hi = bisect_right(f, f[i]-start, 0, i)
            cnt += hi-lo  # 0----lo----hi-----END

        return cnt

    def subarraySumII_TLE(self, A, start, end):
        """
        O(n^2)
        :param A: an integer array
        :param start: start an integer
        :param end: end an integer
        :return:
        """
        n = len(A)
        cnt = 0
        f = [0 for _ in xrange(n+1)]

        for i in xrange(1, n+1):
            f[i] = f[i-1]+A[i-1]  # from left

        for i in xrange(0, n+1):
            for j in xrange(i+1, n+1):
                s = f[j]-f[i]
                if start <= s <= end:
                    cnt += 1

        return cnt
