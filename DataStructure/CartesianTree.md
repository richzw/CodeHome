

The [Cartesian tree](https://en.wikipedia.org/wiki/Cartesian_tree) for a sequence of distinct numbers can be uniquely defined by the following properties:

![](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d5/Cartesian_tree.svg/240px-Cartesian_tree.svg.png)

- The Cartesian tree for a sequence has one node for each number in the sequence. Each node is associated with a single sequence value.
- A symmetric (in-order) traversal of the tree results in the original sequence. That is, the left subtree consists of the values earlier than the root in the sequence order, while the right subtree consists of the values later than the root, and a similar ordering constraint holds at each lower node of the tree.
- The tree has the heap property: the parent of any non-root node has a smaller value than the node itself.[1]

**Cartesian tree sort** is at heart a form of _selection sort_, an algorithm that finds the elements of the output sequence in their sorted order, using data structures to speed up how it finds each element. It builds a Cartesian tree on the input, a tree in which the parent of each value is the larger of the two **nearest smaller values** on either side of it; this can be done in linear time. It maintains a binary heap of active values, initially just the root of the Cartesian tree. And then it repeatedly moves the smallest element of the heap to the output list, replacing it in the heap by its children in the Cartesian tree.

[Ref](http://11011110.livejournal.com/283412.html)
