LEFT_HIGH = 1
EQUAL_HIGH = 0
RIGHT_HIGH = -1
class _AVLMapNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.bfactor = EQUAL_HIGH
        self.left = None
        self.right = None

class AVLMap:
    def __init__(self):
        self._root = None
        self._size = 0

    def __len__(self):
        return self._size

    def __contains__(self, key):
        return self._bstSearch(self._root, key) is not None
       
    def add(self, key, value):
        node = self._bstSearch(key)
        if node is not None:
            node.value = value
            return False
        else:
            (self._root, tmp) = self._avlInsert(self._root, key, value)
            self._size += 1
            return True
    def _avlRotateRight(self, pivot):
        C = pivot.left
        pivot.left = C.right
        C.right = pivot
        return C

    def _avlRotateLeft(self, pivot):
        C = pivot.right
        pivot.right = C.left
        C.left = pivot
        return C

    def _avlLeftBalance(self, pivot):
        C = pivot.left
        if C.bfactor == LEFT_HIGH:
            pivot.bfactor = EQUAL_HIGH
            C.bfactor = EQUAL_HIGH
            pivot = _avlRotateRight(pivot)
            return pivot
        else:
            if G.bfactor == LEFT_HIGH:
                pivot.bfactor = RIGHT_HIGH
                C.bfactor = EQUAL_HIGH
            elif G.bfactor == EQUAL_HIGH:
                pivot.bfactor = EQUAL_HIGH
                C.bfactor = EQUAL_HIGH
            else:
                pivot.bfactor = EQUAL_HIGH
                C.bfactor = LEFT_HIGH
            G.bfactor = EQUAL_HIGH
            pivot.left = _avlRotateLeft(L)
            pivot = _avlRotateRight(pivot)
            return pivot
        
    def  _avlInsert(self, subtree, key, newitem):
        if subtree is None:
            subtree = _AVLTreeNode(key, newitem)
            taller = True
        elif key == subtree.key:
            return (subtree, False)
        elif key < subtree.key:
            (subtree, taller) = _avlInsert(subtree.left, key, newitem)
            if taller:
                if subtree.bfactor == LEFT_HIGH:
                    subtree.right = _avlLeftBalance(subtree)
                    taller = False
                elif subtreee.bfactor == EQUAL_HIGH:
                    subtree.bfactor = LEFT_HIGH
                    taller = True
                else:
                    subtree.bfactor = EQUAL_HIGH
                    taller = False
        else:
            (subtree, taller) = _avlInsert(subtree.right, key, newitem)
            if taller:
                if subtree.bfactor == LEFT_HIGH:
                    subtree.bfactor = EQUAL_HIGH
                    taller = False
                elif subtree.bfactor == EQUAL_HIGH:
                    subtree.bfactor = RIGHT_HIGH
                    taller = True
                else:
                    subtree.right = _avlRightBalance(subtree)
                    taller = False

        return (subtree, taller)
    
    def valueOf(self, key):
        node = self._bstSearch(self._root, key)
        return node.value

    def remove(self, key):
        (self._root, tmp) = self._avlRemove(self._root, key)
        self._size -= 1
