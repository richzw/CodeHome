#!/usr/bin/env python3

'''
物品	 价值	  重量
0       30	   4
1       20	   5
2       40	  10
3       10	   3



第一轮，加入 0 号物品，可以用 4 的重量做到 30 的价值。
第二轮，加入 1 号物品，可以用 5 的重量做到 20 的价值——慢着，我们前一轮已经用 4 的重量做到的 30 的价值，你用 5 才做到 20，这完全没有意义嘛！所以它并没有表现在 F 中。然而如果同时加入 0 号和 1 号物品，我们就可以用 9 的重量做到 50 的价值。这是一个新的信息。
第三轮，再加入 2 号物品，同理，我们只有在重量达到 14，价值达到 70 的时候才是一个新的信息。
第四轮，我们用 3 的重量就做到了 10 的价值，而以前 3 的重量什么也做不出。那么这也是一个新信息。

- 最初我们什么也没有，只有一个元组(0, 0)
- 我们试着加上第 0 号元素，得到了(30, 4)。与最初的元组合并，于是变成了(0, 0), (30, 4)。
- 再试着对每一种情况加上第 1 号元素，得到了(20, 5), (50, 9)。与上一轮的元组合并，由于(20, 5)处于劣势被舍弃了。
  合并的结果是(0, 0), (30, 4), (50, 9)。
- 继续做这个操作，加上第 2 号元素得到(40, 10), (70, 14), (90, 19)。最后一个由于超限被舍弃了，再于上一轮合并，
  得到(0, 0), (30, 4), (50, 9), (70, 14)。
- 最后一轮再加上去，终于得到了最终结果(0, 0), (10, 3), (30, 4), (40, 7), (50, 9), (60, 12), (70, 14)。

Source: http://www.jlao.net/technology/10032/
'''

from collections import deque
import sys
import time
INF = float("inf")


def knapsack(vw, limit, n):
    vw = sorted(vw, key=lambda x: x[1], reverse=True)  # Accelerate
    A = deque([(0, 0)])

    for i in range(0, n):
        B = deque()  # find all possiblities after adding one new item
        for item in A:
            if item[1] + vw[i][1] > limit:  # A is sorted
                break
            B.append((item[0] + vw[i][0], item[1] + vw[i][1]))

        level, merge = -1, deque()  # the bar keeps going up
        while A or B:    # merging the two queues
            ia, ib = A[0][1] if A else INF, B[0][1] if B else INF
            x = A.popleft() if (ia < ib) else B.popleft()
            if x[0] > level:
                merge.append(x)
                level = x[0]
        A = merge
    return A[-1]

if __name__ == "__main__":
    with open(sys.argv[1] if len(sys.argv) > 1 else sys.exit(1)) as f:
        limit, n = map(int, f.readline().split())
        vw = [tuple(map(int, ln.split())) for ln in f.readlines()]

    start = time.time()
    A = knapsack(vw, limit, n)
    end = time.time()
