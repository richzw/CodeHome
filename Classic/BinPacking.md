**Q**:Given N objects and they are 1~n, the volume of the i-th object is ti and ti <= M; Meanwhile, there are many boxes, 
and the volume of each box is M. Now we should put all these objects into boxes with the order of 1~N, what the minimum
number of boxes should be used?

For example, there are 5 objects and their volume are {7,2,5,3,9} with order 1~5. The volume of each box is 10.
So the optimal solution is 3 boxes and they are {7}，{2，5，3}，{9} respectively.

My solution: greedy algorithm. Suppose the optimal solution of the ith object is x boxes are filled and the remaining space is y,
then for the i+1 object, if its volume is larger than y, it has to be put into another new box. Otherwise, one option is 
that put it into the current box, and the solution is (x, y-v); the other option is that put it into another new box, and solution 
is (x+1, M-v)

-1. Next Fit
When processing the next item, see if it fits in the same bin as the last item. Start a new bin only if it does not. Incredibly simple 
   to implement (linear time.)

-2. First Fit
rather than checking just the last bin, we check all previous bins to see if the next item will
	fit. Start a new bin, only when it does not.

-3. Best Fit
The third strategy places the next item in the *tightest* spot. That is, put it in the bin so that smallest empty space is left.

   Example.	0.2, 0.5, 0.4, 0.7, 0.1, 0.3, 0.8
	empty	empty		  empty
	0.1
	0.5		        0.3	
	0.2	     0.4	0.7	    0.8

-4. Fisrt Fit Descreasing
1. Suppose the N items have been sorted in descending order of size;
       s1 > s2 > ... > sN. If the optimal packing uses M bins, then
       all bins in the FFD after M have items of size <= 1/3.

2. The number of items FFD puts in bins after M is at most M-1.
