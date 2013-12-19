Hashing 

	H(key) = key %M
	
Linear probe
 	Slot = (home+i)%
 	
		Home is index to which the key originally mapped by the hash function
		
	Slot = (home +i*c)%M
	
Quadratic probe

	Slot = (home + i^2)%M
	
Double hashing

	Slot = (home + i*hp(key))%M
	
	Hp(key) = 1 + key %P
	
Rehashing

	Enlarge the hash table size and then rebuild the whole hash table.
	
Separate chaining

	Linked list is used to store the individual keys that map to the same entry.
	
Hash function:
	Division
	
	Truncation
		Key: 4873152 = 812 [select digits from specific column]
	Folding
		Key: 4873152 = 48+731+52=831
	Hashing Strings
		Sting ‘hashing’ = 104+97+115+104+105+110+103 = 738
