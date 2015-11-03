def knapsack_pq(vw, limit):
	def bound(v, w, j):
		pass

	maxValue = 0
	PQ = [[-bound(0, 0, 0), 0, 0, 0]]
	while PQ:
		b, v, w, j = heappop(PQ)
		if b <= -maxValue:
			if w + vw[j][1] <= limit:
				maxValue = max(maxValue, v + vw[j][0])
				heappush(PQ, [-bound(v+vw[j][0], w+vw[j][1], j+1),
									v+vw[j][0], w+vw[j][1], j+1])
			if j < len(vw) - 1:
				heappush(PQ, [-bound(v, w, j+1), v, w, j+1])
	return maxValue
