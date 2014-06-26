from random import Random

class UnbalancedCoin:
	'''
	Implementation of unbalance Coin which generate the unequal probability
	'''
	def __init__(self, p, rand=None):
		assert 0.0 < p < 1.0, 'Invalid P'
		self._p = p
		if rand is None:
			rand = Random()
		self._rand = rand
	
	def Flip(self):
		return self._rand.random() < self._p
		
def MakeEqualProb(coin):
	'''
	Get equal probability through unequal coin
	'''
	while True:
		a = coin.Flip()
		if a != coin.Flip():
			return a

# Weighted Random Sample
'''
Given a group of unknown number of data, each element has a non-negative weights. Required to traverse only once,
randomly select an element in which the probability of any one element is selected is proportional to its weight
'''
def WeightedRamdomSample(rand = None):
	selection = None
	total_weight = 0.0
	if rand is None:
		rand = Random()
	while True:
		#outputs the current selection and get the next item
		(item, weight) = yield selection
		total_weight += weight
		if rand.random() * total_weight < weight:
			selection = item

'''
Here is the test codes
'''
# Use an arithmetic sequence as weights
n = 10
# weights are [1, 2, 3, ..., 10]
weights = [i + 1 for i in xrange(n)]
repeat = 100000
occurrences = [0 for i in xrange(n)]
rand = Random()
for i in xrange(repeat):
	selector = WeightedRandomSelect(rand)
	selector.next()
	selection = None
	for item in xrange(n):
		selection = selector.send((item, weights[item]))
	occurrences[selection] += 1
print occurrences


# better solution
# minimum heap - keep the elements in heap by key, which is random key related with weight
#http://www.gocalf.com/blog/weighted-random-selection-2.html
from heapq import *
def WeightedRamdomSample(m=1, rand=None):
	'''
	One special mathmatic formular, key = r^(1/weight), r is one random number between 0 and 1.
	we choose the max key 
	'''
	assert m > 0, 'Invalid m'
	selection = []
	heap = []
	
	if rand is None:
		rand = Random()
	while True:
		(item, weight) = yield selection
		if weight <= 0:
			continue
		key = rand.random() ** (1.0/weight)
		if len(selection) < m:
			heap.append((key, len(selection)))
			selection.append(item)
			if len(selection) == m:
				heapify(heap)
		else:
			if key > heap[0][0]:
				index = heap[0][1]
				heapreplace(heap, (key, index))
				selection[index] = item
