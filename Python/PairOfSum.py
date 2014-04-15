#

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
