#Given an integer array, output all pairs that sum up to a specific value k. 

# O(NlogN)
def mySum(arr, ss):
	if len(arr) < 2:
		return
	arr.sort()
	beginIdx, endIdx = (0, len(arr)-1)
	while beginIdx < endIdx:
		curSum = arr[beginIdx] + arr[endIdx]
		if curSum == ss:
			print arr[beginIdx], arr[endIdx]
			beginIdx += 1
		elif curSum < ss:
			beginIdx += 1
		else:
			endIdx -= 1

# O(N)
def pairOfSum(arr, ss):
	if len(arr) < 2:
		return
	hmap = set()
	result = set()
	for num in arr:
		target = ss - num
		if target not in hmap:
			hmap.add(num)
		else:
			result.add((min(target, num), max(target, num)))
	print '\n'.join(map(str, result))
