class MaxMap:
    def __init__(self, size):
        self._container = Array(size)
        self._count = 0

    def __len__(self):
        return self._count

    def capacity(self):
        return len(self._container)

    def add(self, value):
        assert self._count < self.capacity()
        self._container[self._count] = value
        self._siftUp(self, self._count)
        self._count += 1

    def peek(self):
        value = self._container[0]
        self._count -= 1
        self._container[0] = self._container[self._count]
        self._siftDown(self, 0)

    def _siftUp(self, ndx):
        if ndx > 0:
            parent = ndx // 2
            if self._container[ndx] > self._container[parent]:
                tmp = self._container[ndx]
                self._container[ndx] = self._container[parent]
                self._container[parent] = tmp
                self._siftUp(parent)

    def _siftDown(self, ndx):
        left = 2*ndx + 1
        right = 2*ndx + 2

        large = ndx
        if left < _count and self._container[left] > self._container[large]:
            large = left
        elif right < _count and self._container[right] > self._container[large]:
            large = right

        if large != ndx:
            swap(self._container[large], self._container[ndx])
            self._siftDown(large)
