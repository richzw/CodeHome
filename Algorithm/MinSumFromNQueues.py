'''
Find minimum sum of two numbers

2 12 3 4 
8 2 2
10 10
In the above example I can either choose 2 from first queue and 8 from second or 8 and 2 both from second. Both choices give sum 10.

Example 2:

Find minimum sum of two numbers

4 15 2
8 2 2
10 10
In the above example one has to choose 8 and 2 both from second list.
'''

'''
Let F(qs, k) be the minimum sum from choosing k numbers from the queues qs. Then:

F([], k) = 0 if k == 0, otherwise +infinity.
F([q] + qs, k) = min_i(q[0] + q[1] + ... + q[i-1] + F(qs, k-i) for i in 0...k)

That is, if you've no queues left, the min sum is 0, otherwise, you can take i numbers from the first queue, and k-i from the rest.
'''

def F(qs, n, k, cache):
    if k == 0:
        return 0
    if n == 0:
        return 1e12
    if (n, k) not in cache:
        best = 1e12
        s = 0
        for i in xrange(k+1):
            if i > len(qs[len(qs)-n]):
                break
            if i > 0:
                s += qs[len(qs)-n][i-1]
            best = min(best, s + F(qs, n-1, k-i, cache))
        cache[n, k] = best
    return cache[n, k]

egs = [
    (2, [[2, 2, 3, 4], [8, 2, 2], [10, 10]]),
    (2, [[4, 15, 2], [8, 2, 2], [10, 10]]),
    (3, [[100, 100, 100], [101, 101, 2]])
]

for k, qs in egs:
    print k, qs
    print F(qs, len(qs), k, dict())
    print

