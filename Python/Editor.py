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
	def moveLeft(left):
		if self._curColNdx == 0:
			if self._curLineNdx > 0:
				self.moveUp(1)
				self.moveLineEnd()
		else:
			self._curColNdx -= 1

	def breakLine(self):
		nlContents = self._curLine.text[self._curColNdx:]
		del self._curLine.text[self._curColNdx]
		self._curLine.append('\n')
		# insert the new line and increment the line counter
		self._insertNode(self._curLine, nlContents)
		# move the cursor
		self._curLine = newLine
		self._curLineNdx += 1
		self._curColNdx = 0

	def addChar(self, char):
		if char == '\n':
			self.breakLine()
		else:
			ndx = self._curColNdx
			if self.insertMode():
				self._curLine.text.insert(ndx, char)
			else:
				if self.getChar() == '\n':
					self._curLine.text.insert(ndx, char)
				else:
					self._curLine.text[ndx] = char
			self._curColNdx += 1

	def deleteChar(self):
		if self.getChar() != '\n':
			self._curLine.text.pop(self._curColNdx)
		else:
			if self._curLine is self._lastLine:
				return
			else:
				nextLine = self._curLine.next
				self._curLine.text.pop()
				self._curLine.text.extend(nextLine.text)
				self._removeNode(nextLine)
