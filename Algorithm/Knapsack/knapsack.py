
"""
Source: http://www.jlao.net/technology/10032/
"""

import sys
 
def knapsack(v, w, limit, n):
    F = [[0] * (limit + 1) for x in range(n + 1)] 
    for i in range(0, n):                # F[-1] is all 0.
        for j in range(limit + 1):
            if j >= w[i]:
                F[i][j] = max(F[i - 1][j], F[i - 1][j - w[i]] + v[i])
            else:
                F[i][j] = F[i - 1][j]
    return F
 
if __name__ == "__main__":
    with open(sys.argv[1] if len(sys.argv) > 1 else sys.exit(1)) as f:
        limit, n = map(int, f.readline().split())
        v, w = zip(*[map(int, ln.split()) for ln in f.readlines()])
 
    F = knapsack(v, w, limit, n)
    print("Max value:", F[n - 1][limit])
 
    """ Display selected items"""
    y = limit
    for i in range(n - 1, -1, -1):
        if F[i][y] > F[i - 1][y]:
            print ("item: ", i, "value:", v[i], "weight:", w[i])
            y -= w[i]
            
# one array
def knapsack(v, w, limit, n):
    F = [0] * (limit + 1)
    for i in range(n):
        for j in range(limit, w[i], -1):
            F[j] = max(F[j - w[i]] + v[i], F[j])
    return F


