class _ExpTreeNode:
    def __init__(self, data):
        self.element = data
        self.left = None
        self.right = None

class ExpressionTree:
    def __init__(self, expStr):
        self._expTree = None
        self._buildTree(expStr)

    def evaluate(self, varMap):
        return self._evalTree(self._expTree, varMap)

    def __str__(self):
        return self._buildString(self._expTree)

    def _buildString(self, treeNode):
        if treeNode.left is None and treeNode.right is None:
            return str(treeNode.element)
        else:
            strExp = '('
            strExp += self._buildString(treeNode.left)
            strExp += str(treeNode.element)
            strExp += self._buildString(treeNode.right)
            strExp += ')'
            return strExp

    def _evalTree(self, subtree, varDict):
        if subtree.left is None and subtree.right is None:
            if subtree.element >= '0' and subtree.element <= '9':
                return int(subtree.element)
            else:
                return varDict[subtree.element]
        else:
            lvalue = self._evalTree(subtree.left, varDict)
            rvalue = self._evalTree(subtree.right, varDict)

            return _computeOp(lvalue, subtree.element, rvalue)

    def _computeOp(left, op, right):
        pass

    def _buildTree(self, expStr):
        expQ = Queue()
        for token in expStr:
            expQ.enqueue(token)

        self._expTree = _ExpTreeNode(None)
        self._recBuildTree(self._expTree, expQ)

    def _recBuildTree(self, curNode, expQ):
        token = expQ.dequeue()

        if token == '(':
            curNode.left = _ExpTreeNode(None)
            _recBuildTree(curNode.left, expQ)

            # next token will be an operator: + - * /
            curNode.element = expQ.dequeue()
            curNode.right = _ExpTreeNode(None)
            _recBuildTree(curNode.right, expQ)

            # next token will be ), remove it
            expQ.dequeue()
        else:
            curNode.element = token
