from array import Array2D
from lliststatck import Stack

class _CellPosition(object):
	def __init__(self, row, col):
		self.row = row
		self.col = col

class Maze:
	MAZE_WALL = "*"
	PATH_TOKEN = "x"
	TRIED_TOKEN = "o"

	def __init__(self, numbRows, numCols):
		self._mazeCells = Array2D(numbRows, numCols)
		self._startCell = None
		self._exitCell = None

	def numRows(self):
		return self._mazeCells.numRows()

	def numCols(self):
		return self._mazeCells.numCols()

	def setWall(self, row, col):
		# assert
		self._mazeCells.set(row, col, self.MAZE_WALL)

	def setStart(self, row, col):
		self._startCell = _CellPosition(row, col)

	def setExit(self, row, col):
		self._exitCell = _CellPosition(row, col)

	def findPath(self):
		path = Stack()

		"""
		there are four direction: 
		offset    x     y     option
		left,     -1    0       0
		right,    1     0       1
		up,       0     1       2
		down,     0     -1      3
		"""
		offset = list()
		offset.append(_CellPosition(-1, 0))
		offset.append(_CellPosition(1, 0))			
		offset.append(_CellPosition(0, 1))
		offset.append(_CellPosition(0, -1))

		option = 0
		current = self._startCell
		while _validMove(current.row, current.col) and _exitFound(current.row, current.col): # over the last option
			while option <=3:
				if _validMove(current.row + offset[option].cow, current.col + offset[option].col):   # search direction
					if not _exitFound(current.row + offset[option].cow, current.col + offset[option].col):	
						_markPath(_CellPosition(current.row + offset[option].cow, current.col + offset[option].col))
						option += 1
					else:
						return True
				else:
					break

			if option <= 3: # push the neighbore into path
				path.push(_CellPosition(current.row + offset[option].cow, current.col + offset[option].col))
				_markPath(_CellPosition(current.row + offset[option].cow, current.col + offset[option].col))
				current = _CellPosition(current.row + offset[option].cow, current.col + offset[option].col)
				option = 0
			else:
				if path.empty():
					return False
				else:
					pos = path.peek()  # pop up the tried position
					_markTried(pos.row, pos.col)
					path.pop()



	def _validMove(self, row, col):
		return row >= 0 and row < self.numRows() \
				and col >= 0 and col < self.numCols() \
				and self._mazeCells[row, col] is None

	def _exitFound(self, row, col):
		return row == self._exitCell.row and col == self._exitCell.col

	def _markTried(self, row, col):
		self._mazeCells.set(row, col, self.TRIED_TOKEN)

	def _markPath(self, row, col):
		self._mazeCells.set(row, col, self.PATH_TOKEN)
