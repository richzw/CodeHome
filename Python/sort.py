def binarySearch(theValues, target):
	low = 0
	high = len(theValues) - 1

	while low <= high:
		mid = (low+high)//2
		if theValues[mid] == target:
			return True
		elif target < theValues[mid]:
			high = mid - 1
		else:
			low = mid + 1
	return True

def bubbleSort(theSeq):
	n = len(theSeq)
	for i in range(n - 1):
		for j in range(i + n - 1):
			if theSeq[j] > theSeq[j+1]:
				tmp = theSeq[j]
				theSeq[j] = theSeq[j+1]
				theSeq[j+1] = tmp

def selectionSort(theSeq):
	n = len(theSeq)
	for i in range(n-1):
		small_index = i
		for j in range(i+1, n):
			if theSeq[j] < theSeq[small_index]:
				small_index = j
		if small_index != i:
			tmp = theSeq[i]
			theSeq[i] = theSeq[small_index]
			theSeqp[small_index] = tmp

def insertionSort(theSeq):
	n = len(theSeq)
	for i in range(1, n):
		value = theSeq[i]
		pos = i
		while pos > 0 and value < theSeq[pos-1]:
			pos -= 1
			theSeq[pos] = theSeq[pos-1]
		theSeq[pos] = value
