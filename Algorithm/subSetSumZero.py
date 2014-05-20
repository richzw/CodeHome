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
