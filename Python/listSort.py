from list import List

def insertSortList(List):
	if List is None:
		return None
		
	newList = None
	while List is not None:
		cur = List
		cur.next = None
		List = List.next
		
		newList = addToList(newList, curNode)
	
	return newList

def addToList(List, node):
	if List is None:
		return node
	else:
		cur = List
		head = List
		while List.next is not None \
			and cur.data < node.data:
			List = List.next
			cur = List
		cur.next = node
		
	return head
