class BSTMap:
    def __init__(self):
        self._root = None
        self._size = 0

    def __len__(self):
        return self._size

    def __contains__(self, key):
        return self._bstSearch(self._root, key) is not None

    def valueOf(self, key):
        node = self._bstSearch(self._root, key)
        assert node is not None, "Invalid map key"
        return node

    def _bstSearch(self, subtree, target):
        if subtree is None:
            return subtree
        elif subtree.value < target:
            subtree.right = _bstSearch(subtree.right, target)
        elif subtree.value > target:
            subtree.left = _bstSearch(subtree.left, target)
        else:
            return subtree

    def _bstMin(self, subtree):
        if subtree is None:
            return subtree
        if subtree.left is None:
            return subtree
        else:
            return _bstMin(subtree.left)

    def add(self, key, value):
        node = self._bstSearch(key)
        if node is not None:
            node.value = value
            return False
        else:
            self._root = self._bstInsert(self._root, key, value)
            self._size += 1
            return True

    def _bstInsert(self, subtree, key, value):
        if subtree is None:
            subtree = _BSTMapNode(key, value)
        elif subtree.value < key:
            subtree.right = self._bstInsert(subtree.right, key, value)
        elif subtree.value > key:
            subtree.left = self._bstInsert(subtree.left, key, value)
        return subtree

    def remove(self, key):
        self._root = self._bstRemove(self._root, key)
        self._size -= 1

    def _bstRemove(self, subtree, target):
        if subtree is None:
            return subtree
        elif subtree.value < target:
            subtree.right = self._bstRemove(subtree.right, target)
        elif subtree.value > target:
            subtree.left = self._bstRemove(subtree.left, target)
        else:
            # leaf node
            if subtree.left is None and subtree.right is None:
                return None
            # only one child node
            elif subtree.left is None or subtree.right is None:
                if subtree.left is not None:
                    return subtree.left
                else:
                    return subtree.right
            else: # has two children
                successor = self._bstMin(subtree.right)
                subtree.value = successor.value
                subtree.key = successor.key
                subtree.right = self._bstRemove(subtree.right, successor.key)
                return subtree
