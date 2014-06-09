/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or 
vertically neighboring. The same letter cell may not be used more than once.

For example, Given board =
[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.

Analysis
This is a classic depth first search. The online judge makes this problem tough by enforcing strict time limits. 
The tricky part is to implement DFS in a non-recursive manner, and only backtracking when necessary. 
It implies the following:

Like any graph search, nodes need to be marked as visited.
When backtracking, these nodes need to have their visited status removed.
Therefore there must be some way to efficiently determine if a node is being backtracked in order to remove the visited status.

The solution is to do as follows:
Like normal dfs, push nodes to a stack. But the first time a node is pushed to the stack, mark it as visited and do not pop 
it from the stack
When backtracking, that node will appear again. It then needs to be marked as unvisited when seen again, 
and only then is it popped from the stack.
Marking a node as visited can be done many ways. A nice trick is to use the most signficant bit to determine 
if the node has been visited or not.
*/


