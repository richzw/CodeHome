 Solution 1. hash table + BST
  query O(logN)
  
 ```
 less(n1, n2)
  if n1.freq < n2.freq
    return true
  if n1.freq == n2.freq
    return n1.tick < n2.tick
  return false
 ```
  
 Solution 2. hash table + hash (Double linked list) [freq list]
  query O(1)
  
 use min_freq to track the current min freq for eviction
 
 
 
 
