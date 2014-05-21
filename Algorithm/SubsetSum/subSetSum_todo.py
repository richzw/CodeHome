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
