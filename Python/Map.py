# storage class for holding the key/value pairs
class _MapEntry:
	def __init__(self, key, value):
		self.key = key
		self.value = value

class Map:
	def __init__(self):
		self._entryList = list()

	def __len__(self):
		return len(self._entryList)

	def __contains__(self, key):
		ndx = self._findPosition(key)
		return ndx is not None

	def add(self, key, value):
		ndx = self._findPosition(key)
		if ndx is not None:
			self._entryList[ndx].value = value
		else:
			entry = _MapEntry(key, value)
			self._entryList.append(entry)
			return True
	def _findPosition(self, key):
		for i in range(len(self)):
			if self._entryList[i].key == key:
				return i
		return None

	def valueOf(self, key):
		ndx = self._findPosition(key)
		assert ndx is not None, "Invalid map key"
		return self._entryList[ndx].value

	def remove(self, key):
		ndx = self._findPosition(key)
		assert ndx is not None, "Invalid map key"
		self._entryList.pop(ndx)

	def __iter__(self):
		pass
