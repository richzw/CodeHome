
What is the distributed algorithm to determine the median of arrays of integers located on different computers?
----

In a situation like there are a number of servers, each  server is holding a billion integers and medium of integers 
in all servers combined must be found.

----------

**Answer 1**

Suppose you have a master node (or are able to use a consensus protocol to elect a master from among your servers). 
The master first queries the servers for the size of their sets of data, call this n, 
so that it knows to look for the k = n/2 largest element.

The master then selects a random server and queries it for a random element from the elements on that server.  
The master broadcasts this element to each server, and each server partitions its elements into those larger than or 
equal to the broadcasted element and those smaller than the broadcasted element.

Each server returns to the master the size of the larger-than partition, call this m.  
If the sum of these sizes is greater than k, the master indicates to each server to disregard the less-than set 
for the remainder of the algorithm.  If it is less than k, then the master indicates to disregard the larger-than sets and
updates k = k - m.  If it is exactly k, the algorithm terminates and the value returned is the pivot selected 
at the beginning of the iteration.

If the algorithm does not terminate, recurse beginning with selecting a new random pivot from the remaining elements.

[Link](http://www.quora.com/Distributed-Algorithms/What-is-the-distributed-algorithm-to-determine-the-median-of-arrays-of-integers-located-on-different-computers)

------

**A 2**

1. Sort numbers on each machine. 
2. Make a mean heap of N elements by taking 1st element from each machine along with the information to which machine number belongs. 
3. Now remove the minimum element (top of heap), and add the number from the same machine as removed element. Again min heapify. 
4. Repeat 3 for (N*One million)/2 + 1 times. Min element of the heap is required median. 


----

**A 3**

每台机器自己m个数排序，用mlogm次运算。每台机器出一个数，让所有其他机器报出这个数在该机器上的序位，用nlogm次运算。
每台机器在自己的已排好序的m个数中产生最接近全局中位数的候选，共可选用logm次。总共就是n(logm)^2+mlogm次。
