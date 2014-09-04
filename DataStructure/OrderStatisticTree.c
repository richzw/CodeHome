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
