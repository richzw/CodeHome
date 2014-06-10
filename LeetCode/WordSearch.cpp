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

class Solution:
    # @param board, a list of lists of 1 length string
    # @param word, a string
    # @return a boolean
    def exist(self, board, word):
        self.totalRow, self.totalCol = len(board), len(board[0])
        for i in xrange(self.totalRow):
            for j in xrange(self.totalCol):
                if board[i][j] == word[0]:
                    if self.dfs(board, i, j, word[1:]): return True
        return False
         
    def dfs(self, board, r, c, word):
        if len(word) == 0: return True
        # Up
        if (r > 0 and board[r - 1][c] == word[0]):
            ch, board[r][c] = board[r][c], '#'
            if self.dfs(board, r - 1, c, word[1:]): return True
            board[r][c] = ch
        # Down
        if (r < self.totalRow - 1 and board[r + 1][c] == word[0]):
            ch, board[r][c] = board[r][c], '#'
            if self.dfs(board, r + 1, c, word[1:]): return True
            board[r][c] = ch
        # Left
        if (c > 0 and board[r][c - 1] == word[0]):
            ch, board[r][c] = board[r][c], '#'
            if self.dfs(board, r, c - 1, word[1:]): return True
            board[r][c] = ch    
        # Right
        if (c < self.totalCol - 1 and board[r][c + 1] == word[0]):
            ch, board[r][c] = board[r][c], '#'
            if self.dfs(board, r, c + 1, word[1:]): return True
            board[r][c] = ch    
        return False

//Like any graph search, nodes need to be marked as visited.
//When backtracking, these nodes need to have their visited status removed.
class Solution {
private:
    bool _exist(vector<vector<char> > &board, string& word, int ptr, 
				vector<vector<bool> > &visited, int row, int col, 
				const int rowCount, const int colCount){
        if (row < 0 || row >= rowCount || col < 0 || col >= colCount){
            return false;
        }
        if (visited[row][col]){
            return false;
        }
        if (ptr == word.length() - 1){
            return board[row][col] == word[ptr];
        }
        if (board[row][col] != word[ptr]){
            return false;
        }
 
        visited[row][col] = true;
        int result = _exist(board, word, ptr + 1, visited, row - 1, col, rowCount, colCount) ||
                     _exist(board, word, ptr + 1, visited, row + 1, col, rowCount, colCount) ||
                     _exist(board, word, ptr + 1, visited, row, col - 1, rowCount, colCount) ||
                     _exist(board, word, ptr + 1, visited, row, col + 1, rowCount, colCount);
        visited[row][col] = false;
        return result;
    }
public:
    bool exist(vector<vector<char> > &board, string word) {
        if (board.empty()){
            return false;
        }
        if (board[0].empty()){
            return false;
        }
        if (word.length() == 0){
            return true;
        }
        int rowCount = board.size();
        int colCount = board[0].size();
        vector<vector<bool> > visited(rowCount, vector<bool>(colCount, false));
        for (int row = 0; row < rowCount; row++){
            for (int col = 0; col < colCount; col++){
                if (_exist(board, word, 0, visited, row, col, rowCount, colCount)){
                    return true;
                }
            }
        }
        return false;
    }
};
