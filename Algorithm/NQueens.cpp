//use 1-D array to solve N Queens questions
class QueenBoard{
public:
	QueenBoard(int size):m_size(size), m_queens(0){
		m_pboard = new int[size+1];
		for (int i = 0; i < size; ++i)
			*(m_pboard+i) = 0;
	}

	~QueenBoard()
	{
		if (m_pboard != NULL){
			delete m_pboard;
			m_pboard = NULL;
		}
	}

	int size() { return m_size; }
	int numQueens() { return m_queens; }

	// the base of row and col are 1
	void removeQueen(int row, int col)
	{
		*(m_pboard+row) = 0;
		--m_queens;
	}

	void placeQueen(int row, int col)
	{
		*(m_pboard+row) = col;
		++m_queens;
	}

	bool unguarded(int row, int col)
	{
		if (is_same_row(row, col) || is_same_col(row, col)
			|| is_same_diagonal(row, col, 1, 1)
			|| is_same_diagonal(row, col, -1, -1)
			|| is_same_diagonal(row, col, 1, -1)
			|| is_same_diagonal(row, col, -1, 1))
			return false;

		return true;
	}

	bool is_same_row(int row, int col)
	{
		// case: same row
		if (*(m_pboard+row) != 0)
			return true;
	}

	bool is_same_col(int row, int col)
	{
		// case: same col
		for (int i = 0; i < m_size; ++i)
		{
			if (*(m_pboard+row) == col)
				return true;
		}
		return false;
	}

	bool is_same_diagonal(int row, int col, int updown, int frontback)
	{
		int step = 1;
		while(row >= 1 && row <= m_size && col >= 1 && col <= m_size)
		{
			int new_row = row + frontback*step;
			int new_col = col + updown*step;

			if (is_same_row(new_row, new_col) || is_same_col(new_row, new_col))
				return true;

			++step;
		}

		return false;
	}

	int solveNQueens(QueenBoard board, int col)
	{
		if (board.numQueens() == board.size())
			return true;
		else{
			for (int row = 0; row < board.size(); ++row){
				if (board.unguarded(row, col)){
					board.placeQueen(row, col);
					if (board.solveNQueens(board, col+1))
						return true;
					else
						board.removeQueen(row, col);
				}
			}
		}

		return false;
	}
private:
	int m_size;
	int m_queens;
	int* m_pboard;
};

