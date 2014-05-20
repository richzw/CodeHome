# NP-Hard issue
'''
我们假定输入序列为：
 x1, ..., xn 
我们需要判断是否存在某个非空子集，使得子集中的数字和为0。

我们序列中负数的和为N，正数的和为P。
定义函数Q(i, s)，它的涵义为: 是否存在x1, ..., xi的非空子集，使得子集中的数字和为s, 子集合加总问题的答案即为Q(n, 0)。
 
显然，如果s < N或者s > P，则Q(i,s) = false，因此无需记录这些值。我们把Q(i, s)的值保存在数组中，其中1 ≤ i ≤ n且N ≤ s ≤ P。
 
接下来使用循环来填充数组。首先，对于N ≤ s ≤ P，设定
 Q(1, s) := (x1 = s) 
随后，对于i = 2, …, n和N ≤ s ≤ P，设定
 Q(i, s) := Q(i - 1, s) 或 (xi = s) 或 Q(i - 1, s - xi) 
算法运行的总时间为O(n(P - N))。
'''

import random
from time import time
from itertools import product

# create a zero matrix of size a (row), b(col)
def create_zero_matrix(a,b):
    return [[0]*b for x in xrange(a)]

# generate a list of size num with random integers with an upper and lower bound
def random_ints(num, lower=-1000, upper=1000):
    return [random.randrange(lower,upper+1) for i in range(num)]

# split a list up into N and P where N be the sum of the negative values and P the sum of the positive values.
# 0 does not count because of additive identity
def split_sum(A):
    N_list = 0
    P_list = 0
    for x in A:
        if x < 0:
            N_list += x
        elif x > 0:
            P_list += x
    return [N_list, P_list]

# since the column indexes are in the range from 0 to P - N
# we would like to retrieve them based on the index in the range N to P
# n := row, m := col
def get_element(table, n, m, N):
    if n < 0:
        return 0
    try:
        return table[n][m - N]
    except:
        return 0

# same definition as above
def set_element(table, n, m, N, value):
    table[n][m - N] = value

# input array
#A = [1, -3, 2, 4]
A = random_ints(200)

[N, P] = split_sum(A)

# create a zero matrix of size m (row) by n (col)
#
# m := the number of elements in A
# n := P - N + 1 (by definition N <= s <= P)
#
# each element in the matrix will be a value of either 0 (false) or 1 (true)
m = len(A)
n = P - N + 1;
table = create_zero_matrix(m, n)

# set first element in index (0, A[0]) to be true
# Definition: Q(1,s) := (x1 == s). Note that index starts at 0 instead of 1.
set_element(table, 0, A[0], N, 1)

# iterate through each table element
#for i in xrange(1, m): #row
#    for s in xrange(N, P + 1): #col
for i, s in product(xrange(1, m), xrange(N, P + 1)):
    if get_element(table, i - 1, s, N) or A[i] == s or get_element(table, i - 1, s - A[i], N):
        #set_element(table, i, s, N, 1)
        table[i][s - N] = 1

# find zero-sum subset solution
s = 0
solution = []
for i in reversed(xrange(0, m)):
    if get_element(table, i - 1, s, N) == 0 and get_element(table, i, s, N) == 1:
        s = s - A[i]
        solution.append(A[i])


##################################################################################################
# from hacker news 
def subset_summing_to_zero (activities):
  subsets = {0: []}
  for (activity, cost) in activities.iteritems():
      old_subsets = subsets
      subsets = {}
      for (prev_sum, subset) in old_subsets.iteritems():
          subsets[prev_sum] = subset
          new_sum = prev_sum + cost
          new_subset = subset + [activity]
          if 0 == new_sum:
              new_subset.sort()
              return new_subset
          else:
              subsets[new_sum] = new_subset
  return []
