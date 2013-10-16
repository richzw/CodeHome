class Set:
	def __init__(self):
		self._theElements = list()

	def __len__(self):
		return len(self._theElements)

	def __contains__(self, elem):
		return elem in self._theElements

	def add(self, elem):
		if elem not in self:
			self._theElements.append(elem)

	def remove(self, elem):
		assert elem in self, "The element must be in the set"
		self._theElements.remove(elem)

'''
	def __eq__(self, setB):
		if len(self) != len(setB):
			return False
		else:
			return self.isSubsetOf(setB)
'''
	def __eq__(self, setB):
		if len(self) != len(setB):
			return False
		else:
			for i in range(len(self)):
				if self._theElements[i] != setB._theElements[i]:
					return False
			return True

	def _findPosition(self, target):
		low = 0
		high = len(self) - 1
		while low <= high:
			mid = (low+high)//2
			if _theElements[mid] == target:
				return mid
			elif target < _theElements[mid]:
				high = mid - 1
			else:
				low = mid + 1
		return low

	def isSubsetOf(self, setB):
		for elem in self:
			if elem not in setB:
				return False
		return True

"""
	def union(self, setB):
		newSet = Set()
		newSet._theElements.extend(self._theElements)
		for elem in setB:
			if elem not in self:
				newSet._theElements.append(elem)
		return newSet
"""

	def union(self, setB):
		newSet = Set()
		a = 0
		b = 0

		while a < len(self) and b < len(setB):
			valueA = self._theElements[a]
			valueB = self._theElements[b]
			if valueA < valueB:
				newSet._theElements.append(valueA)
			elif valueA > valueB:
				newSet._theElements.append(valueB)
			else:
				newSet._theElements.append(valueA)
				a += 1
				b += 1
		while a < len(self):
			newSet._theElements.append(self._theElements[a])
			a += 1
		while b < len(setB):
			newSet._theElements.append(self._theElements[b])
			b += 1
		return newSet

	def interset(self, setB):
		newSet = Set()
		for elem in setB:
			if elem in self:
				newSet._theElements.append(elem)
		return newSet

	def difference(self, setB):
		newSet = Set()
		newSet._theElements.extend(self._theElements)
		for elem in setB:
			if elem in newSet:
				newSet.remove(elem)
			else:
				newSet.append(elem)
		return newSet

	def __iter__(self):
		return _SetIterator(self._theElements)

class _SetIterator:
	pass
