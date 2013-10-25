
class _EditBufferNode:
	def __init__(self, text):
		self.text = text
		self.prev = None
		self.next = None

class EditBuffer:
	def __init__(self):
		self._firstLine = _EditBufferNode(['\n'])
		self._lastLine = self._firstLine
		self._curLine = self._firstLine
		self._curLineNdx = 0
		self._curColNdx = 0
		self._numLines = 1
		self._insertMode = True

	def numLines(self):
		return self._numLines

	def numChars(self):
		return len(self._curLine.text)

	def lineIndex(self):
		return self._curLineNdx 

	def columnIndex(self):
		return self._curColNdx

	def setEntryMode(self, insert):
		self._insertMode = insert

	def toggleEntryMode(self):
		self._insertMode = not self._insertMode

	def insertMode(self):
		return self._insertMode == True

	def getChar(self):
		return self._curLine.text[self._curColNdx]

	def getLine(self):
		lineStr = ""
		for char in self._curLine.text:
			lineStr += char
		return lineStr

	def moveLineHome(self):
		self._curLineNdx = 0

	def moveLineEnd(self):
		self._curColNdx = self.numChars() - 1

	def moveUp(self, nlines):
		if nlines <= 0:
			return
		elif self._curLineNdx - nlines < 0:
			nlines = _curLineNdx

		for i in range(nlines):
			self._curLine = self._curLine.prev

		self._curLineNdx -= nlines
		if self._curColNdx >= self.numChars():
			self.moveLineEnd()
