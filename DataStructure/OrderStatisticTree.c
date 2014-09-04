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
