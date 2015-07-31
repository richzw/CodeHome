

The [Cartesian tree](https://en.wikipedia.org/wiki/Cartesian_tree) for a sequence of distinct numbers can be uniquely defined by the following properties:

![](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d5/Cartesian_tree.svg/240px-Cartesian_tree.svg.png)

- The Cartesian tree for a sequence has one node for each number in the sequence. Each node is associated with a single sequence value.
- A symmetric (in-order) traversal of the tree results in the original sequence. That is, the left subtree consists of the values earlier than the root in the sequence order, while the right subtree consists of the values later than the root, and a similar ordering constraint holds at each lower node of the tree.
- The tree has the heap property: the parent of any non-root node has a smaller value than the node itself.[1]
