/*
Q: I want one data structure like that:
1. Insert any element(should be able to contain repetetive ones) in O(log(n)) time
2. Remove an element in O(log(n)) time as well.
3. If i want to query for the number of elemenes in range [a,b], I should get that count in O(log(n)) time..

A:
1. The two obvious data structures for this task are the skip list
2. Some variant of the order statistic tree

An order statistic tree stores one extra piece of information in each node. You can store any of a number of different things,
but the one I find easiest to understand is if each node stores the number of elements in its left sub-tree.

When you insert, as you walk down the tree to store an element, you increment the count every time you descend to
the left in the tree. Since you're only modifying the nodes you'd traverse anyway, this doesn't change the O(log N) insertion.
When you re-balance, you have to adjust accordingly (but, again, you're only modifying counts in nodes
you're already modifying when you do rotations, so (again) you don't affect the overall complexity.

When you need to find a distance from one element to another, you just find the two nodes, each with O(log N) complexity. 
You get the index of each element in the tree as you find it by initializing an index from the root, 
then updating it from there (subtract the count as you descend to the left, add as you descend to the right).
*/

/*
 an order statistic tree is a variant of the binary search tree (or more generally, a B-tree[1]) 
 that supports two additional operation beyond insertion, lookup and deletion:

Select(i) — find the i'th smallest element stored in the tree
Rank(x) – find the rank of element x in the tree, i.e. its index in the sorted list of elements of the tree
*/

function Select(t, i)
    // Returns the i'th element (zero-indexed) of the elements in t
    r ← size[left[t]]
    if i = r
        return key[t]
    else if i < r
        return Select(left[t], i)
    else
        return Select(right[t], i - (r + 1))
        
Rank(root, x):
  if root is null:
    error: not found
  else if x < root.key:
    return Rank(root.left, x)
  else if x = root.key:
    if root.left is not null:
      return root.left.count + 1
    else:
      return 1
  else if x > root.key:
    if root.left is not null:
      return root.left.count + 1 + Rank(root.right, x)
    else:
      return 1 + Rank(root.right, x)
      
      
FindByRank(root, k):
  if root is null:
    error: not found

  if root.left is null:
    leftcount = 0
  else:
    leftcount = root.left.count
  
  if k <= leftcount:
    return FindByrank(root.left, k)
  else if k = leftcount + 1:
    return root
  else if k > leftcount + 1:
    return FindByRank(root.right, k - leftcount - 1)
