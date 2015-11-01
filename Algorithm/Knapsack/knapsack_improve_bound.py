import sys
import logging

def knapsack(vw, limit):
	def bound(v, w, j):
		if j >= len(vw) or w > limit:
			return -1
		else:
			while j < len(vw) and w + vw[j][1] <= limit:
				v, w, j = v+vw[j][0], w+vw[j][1], j + 1
			if j < len(vw):
				v += (limit - w)*vw[j][0]/(vw[j][0] * 1.0)
			return v

	def traverse(v, w, j):
		nonlocal maxValue
		if bound(v, w, j) >= maxValue:
			if w + vw[j][1] <= limit:
				maxValue = max(maxValue, v + vw[j][0])
				traverse(v+vw[j][0], w+vw[j][1], j+1)
			if j < len(vw) - 1:
				traverse(v, w, j+1)

	maxValue = 0
	traverse(0, 0, 0)
	return maxValue

if __name__ == '__main__':
    try:
	    with open(sys.argv[1] if len(sys.argv) > 1 else sys.exit(1)) as f:
		    limit, n = map(int, f.readline().split())
		    vw = []
		    for ln in f.readlines():
		    	vl, wl = tuple(map(int, ln.split()))
		    	vw.append([vl, wl, vl/(wl*1.0)])
		    knapsack(sorted(vw, key=lambda x: x[2], reverse=True), limit)
    except IOError as e:
        logging.exception(e)

