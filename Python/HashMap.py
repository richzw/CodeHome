from array import Array

class _MapEntry:
    def __init__(self, key, value):
        self.key = key
        self.value = value

class HashMap:
    UNUSED = None
    EMPTY = _MapEntry(None, None)

    def __init__(self):
        self._table = Array(7)
        self._count = 0
        self._maxCount = len(self._table) - len(self._table)//3

    def __len__(self):
        return self._count

    def __contains__(self, key):
        slot = self._findSlot(key, False)
        return slot is not None

    def _hash1(self, key):
        return abs(hash(key))%len(self._table)
    def _hash2(self, key):
        return 1 + abs(hash(key))%(len(self._table) - 2)
    
    #forInsert indicates if the search is for an insertion, 
    #which locates the slot into which the new key can be added.
    def _findSlot(self, key, forInsert):
        slot = self._hash1(key)
        step = self._hash2(key)

        M = len(self._table)
        while self._table[slot] is not UNUSED:
            if forInsert and \
                (self._table[slot] is UNUSED or self._table[slot] is EMPTY):
                return slot
            elif not forInsert and \
                (self._table[slot] is not EMPTY and self._table[slot].key == key):
                return slot
            else:
                slot = (slot+step)%M

    def _rehash(self):
        origTable = self._table
        newSize = len(self._table)*2 + 1
        self._table = Array(newSize)

        self._count = 0
        self._maxCount = newSize - newSize//3

        for entry in origTable:
            if entry is not UNUSED and entry is not EMPTY:
                slot = self._findSlot(key, True)
                self._table[slot] = entry
                self._count += 1

    def valueOf(self, key):
        slot = self._findSlot(key, False)
        assert slot is not None, "Invalid map key"
        return self._table[slot].value

    def add(self, key, value):
        if key in self:
            slot = self._findSlot(key, False)
            self._table[slot].value = value
            return False
        else:
            slot = self._findSlot(key, True)
            self._table[slot] = _MapEntry(key, value)
            self._count += 1
            if self._count == self._maxCount:
                self._rehash()
            return True




