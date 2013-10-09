def assoc_list_find(alist, elem):
	for k, v in alist:
		if elem == k:
			return v
	else:
		raise KeyError(elem)
		
al = [[1,2], [3,4], [5,6], [7,9]]
print(assoc_list_find(al, 5))
print(assoc_list_find(al, 9))
