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
 	Slot = (home+i)%
 	
		Home is index to which the key originally mapped by the hash function
		
	Slot = (home +i*c)%M
	
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


***Consistent Hashing***:

Now we consider the common way to do load balance. The machine number chosen to cache object o will be: `hash(o) mod n`

When we add or remove machine from machine group. The new location will be calculated again.

`Hash(o) mod (n+1)`  add a machine
`Hash(o) mod (n-1)`  remove a machine.

Consistent hashing can guarantee that when a cache machine is removed, only the objects cached in it will be rehashed; when a new cache machine is added, only a fairly few objects will be rehashed.

***SimHash***:


***Merkle Hash Tree***:


***Bloom Filter***:



