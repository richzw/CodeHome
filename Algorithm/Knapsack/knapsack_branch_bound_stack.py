def knapsack(vw, limit):
	def bound(v, w, j):
		if j >= len(vw) and w > limit:
			return -1
		else:
			while j < len(vw) and w + vw[j][1] <= limit:
				v, w, j = v+vw[j][0], w+vw[j][1], j + 1
			if j < len(vw):
				v += (limit - w)*vw[j][0]/(vw[j][1] * 1.0)

	maxValue = 0
	stack = [[0, 0, 0]]

	while stack:
		v, w, j = stack.pop()
		if bound(v, w, j) >= maxValue:
			if j < len(vw) - 1:
				stack.append([v, w, j + 1])
			if w + vw[j][1] <= limit:
				maxValue = max(maxValue, v + vw[j][0])
				stack.append([v+vw[j][0], w+vw[j][1], j + 1])

	return maxValue
	
