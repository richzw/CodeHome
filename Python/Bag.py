#implements the Bag ADT using python list
class Bag:
	def __init__(self):
		self._theItems = list()

	def __len__(self):
		return len(self._theItems)

	def __contains__(self, item):
		return item in self._theItems

	def add(self, item):
		self._theItems.append(item)

	def remove(self, item):
		assert item in self._theItems, "The item must be in the bag"
		ndx = self._theItems.index(item)
		return self._theItems.pop(ndx)

	def __iter__(self, item):
		return _BagIterator(self._theItems)

class _BagIterator:
	def __init__(self, theList):
		self._bagItems = theList
		self._curItem = 0

	def __iter__(self):
		return self

	def __next__(self):
		if self._curItem < len(self._bagItems):
			item = self._bagItems[self._curItem]
			self._curItem += 1
			return item
		else:
			raise StopIteration
			
class _BagListNode(object):
	def __init__(self, item):
		self.item = item
		self.next = None

class Bag:
	def __init__(self):
		self._head = None
		self._size = 0
	def __len__(self):
		return self._size

	def __contains__(self, target):
		curNode = self._head
		while curNode is not None and curNode.item != target:
			curNode = curNode.next
		return curNode is not None
	def add(self, item):
		newNode = _BagListNode(item)
		newNode.next = self._head
		self._head = newNode
		self._size += 1

	def remove(self, item):
		preNode = None
		curNode = self._head
		while curNode is not None and curNode.item != item:
			preNode = curNode
			curNode = curNode.next

		assert curNode is not None, "The item must be in the bag"
		
		self._size -= 1
		if curNode is head:
			self._head = curNode.next
		else:
			preNode.next = curNode.next
		return curNode.item

	def __iter__(self):
		return _BagIterator(self._head)

class _BagIterator:
	def __init__(self, listHead):
		self._curNode = listHead

	def __iter__(self):
		return self

	def next(self):
		if self._curNode is None:
			raise StopIteration
		else:
			item = self._curNode.item
			self._curNode = self._curNode.next
			return item					
