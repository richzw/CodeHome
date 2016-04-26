
Binary tree tranverse iteratively

```
iterativePreorder(node)
s <- empty stack
while (!s.isEmpty() or node != null)
  if (node != null)
    visit(node)
    if (node.right)
      s.push(node.right)
    node <- node.left
  else
    node <- s.pop()
```

```
iterativeInorder(node)
s <- empty stack
while (!s.isEmpty() or node != null)
  if (node != null)
    s.push(node)
    s <- s.left
  else
    node <- s.pop()
    visit(node)
    node <- node.right
```

```
iterativePostorder(node)
s <- empty stack
lastNodeVisited <- null
while (!s.isEmpty() or node != null)
  if (node != null)
    s.push(node)
    s <- s.left
  else
    peekNode <- s.peek()
    

```
