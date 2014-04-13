'''
Given an array:
[a_1, a_2, ..., a_N, b_1, b_2, ..., b_N, c_1, c_2, ..., c_N ]  
convert it to:
[a_1, b_1, c_1, a_2, b_2, c_2, ..., a_N, b_N, c_N]  
in-place using constant extra space.

- See more at: http://www.ardendertat.com/2011/10/18/programming-interview-questions-9-convert-array/#sthash.6SpyNsBJ.dpuf
'''


def convertArr(arr):
	N = len(arr)/3
	for currentIdx in range(len(arr)):
		swapIdx = getIndex(currentIdx, N)
		while swapIdx < currentIdx:
			swapIdx = getIndex(swapIdx, N)
		arr[currentIdx], arr[swapIdx] = arr[swapIdx], arr[currentIdx]

def getIndex(idx, num):
	return (idx%3)*num + (idx/3)
