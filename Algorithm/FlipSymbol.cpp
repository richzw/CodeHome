/*
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region .

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:
X X X X
X X X X
X X X X
X O X X
*/
/*
1. First scan the four edges of the board, if you meet an 'O',
call a recursive mark function to mark that region to something else (for example, '+');
2. scan all the board, if you meet an 'O', flip it to 'X';
3. scan again the board, if you meet an '+', flip it to 'O';
*/
// version 1. BFS
void visit_bfs(int i, int j, queue<int> q, vector<vector<int> > board){
	int m = board.size(), n = board[0].size();
	if (i < 0 || i > m-1 || j < 0 || j > n-1 || board[i][j] != 'O')
		return;
	board[i][j] = '+';
	q.push(i*n + j); // save the index of array
}

void bfs(int i, int j, vector<vector<int> > board){
	queue<int> q;
	visit_bfs(i, j, q, board);
	
	while(!q.empty()){
		int cur = q.front();
		int row = cur/board[0].size();
		int col = cur%board[0].size();
		visit_bfs(row-1, col, q, board);
		visit_bfs(row, col-1, q, board);
		visit_bfs(row+1, col, q, board);
		visit_bfs(row, col+1, q, board);

		q.pop();
	}
}

void solve_bfs(vector<vector<int> > board){
	if (board.size() == 0)
		return;
	int m = board.size(), n = board[0].size();
	
	for (int i = 0; i < n; ++i){
		bfs(0, i, board);
		bfs(m-1, i, board);
	}

	for (int j = 0; j < m-1; ++j){
		bfs(j, 0, board);
		bfs(j, n-1, board);
	}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j){
			if (board[i][j] == 'O')
				board[i][j] = 'X';
			else if (board[i][j] == '+')
				board[i][j] = 'O';
		}
}

// version 2. dfs
void dfs(int i, int j, vector<vector<int> > board){
	int m = board.size(), n = board[0].size();
	if (i < 0 || i > m-1 || j < 0 || j > n-1 || board[i][j] != 'O')
		return;

	board[i][j] = '+';
	dfs(i-1, j, board);
	dfs(i, j-1, board);
	dfs(i+1, j, board);
	dfs(i, j+1, board);
}
