class tree:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

        
def findSum(tree, target):
    # post-order traverse
    if tree.left is not None:
        findSum(tree.left, target)
    if tree.right is not None:
        findSum(tree.right, target)

    tree.sums = [tree.data]

    # add this node to the sums of children
    if tree.left is not None:
        for left_sum in tree.left.sums:
            tree.sums.append(left_sum + tree.data)
    if tree.right is not None:
        for right_sum in tree.right.sums:
            tree.sums.append(right_sum + tree.data)

    if target in tree.sums:
        print "Found the sum in the root node"

    if tree.left is not None and tree.right is not None:
        for left_sum in tree.left.sums:
            if target-left_sum in tree.right.sums:
                print "Found the sum in here"

    if tree.left:
        delete tree.left.sums
    if tree.right:
        delete tree.right.sums
