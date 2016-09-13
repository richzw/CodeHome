Hashing
----
#####Hash function:
	Division
		H(key) = key %M	
	Truncation
		Key: 4873152 = 812 [select digits from specific column]
	Folding
		Key: 4873152 = 48+731+52=831
	Hashing Strings
		Sting ‘hashing’ = 104+97+115+104+105+110+103 = 738
	
#####Linear probe
 	Slot = (home+i) % M
 	
		Home is index to which the key originally mapped by the hash function
		
	Slot = (home +i*c) % M
	
#####Quadratic probe

	Slot = (home + i^2)%M
	
#####Double hashing

	Slot = (home + i*hp(key))%M
	
	Hp(key) = 1 + key %P

#####Separate chaining

	Linked list is used to store the individual keys that map to the same entry.
	
#####Rehashing

	Enlarge the hash table size and then rebuild the whole hash table.
	
	Hash algorithm in redis:
1.	MurmruHash, http://code.google.com/p/smhasher/
2.	Based on djb hash algorithm.

#####[LeapFrog](http://preshing.com/20160314/leapfrog-probing/)

![](https://cloud.githubusercontent.com/assets/1590890/18465717/bcf53bea-79ca-11e6-8d95-59c9bda05705.png)

To find a given key, proceed as follows:

- First, hash the key and compute its modulus to get the bucket index. That’s the item’s ideal cell. Check there first.
- If the item isn’t found in that cell, use that cell’s first delta value to determine the next cell to check. Just add the delta value to the current array index, making sure to wrap at the end of the array.
- If the item isn’t found in that cell, use the second delta value for all subsequent cells. Stop when the delta is zero.

For the strategy to work, there really needs to be two delta values per cell. The first delta value directs us to the desired bucket’s probe chain (if not already in it), and the second delta value keeps us in the same probe chain.

For example, suppose we look for the key 40 in the above table, and 40 hashes to 0x674a0243. The modulus (last digit) is 3, so we check index 3 first, but index 3 contains an item belonging to a different bucket. The first delta value at index 3 is 2, so we add that to the current index and check index 5. The item isn’t there either, but at least index 5 contains an item belonging to the desired bucket, since its hash also ends with 3. The second delta value at index 5 is 3, so we add that to the current index and check index 8. At index 8, the hashed key 0x674a0243 is found.


***Consistent Hashing***:

Now we consider the common way to do load balance. The machine number chosen to cache object o will be: `hash(o) mod n`

When we add or remove machine from machine group. The new location will be calculated again.

`Hash(o) mod (n+1)`  add a machine
`Hash(o) mod (n-1)`  remove a machine.

Consistent hashing can guarantee that when a cache machine is removed, only the objects cached in it will be rehashed; when a new cache machine is added, only a fairly few objects will be rehashed.

***SimHash***:

- Split strings into words

    the cat sat on the mat -> {"th", "he", "e ", " c", "ca", "at", "t ", " s", "sa", " o", "on", "n ", " t", " m", "ma"}
    ”th”.weight = 5, “he”.weight = 3

- Hash words

    "th".hash = 100110 , "he".hash = 110000

- Add weight

    ”th” = 5 -5 -5 5 5 -5, “he” = 3 3 -3 -3 -3 -3

- Combine

    ”th”+”he” = 8 -2 -8 2 2 -8 

- Dimensionality reduction

    8 -2 -8 2 2 -8 = 1 0 0 1 1 0


***Merkle Hash Tree***:


***Bloom Filter***:

a space-efficient probabilistic data structure that is used to test whether an element is a member of a set.
- False positive matches are possible
- but false negatives are not
- Easy to insert and test





