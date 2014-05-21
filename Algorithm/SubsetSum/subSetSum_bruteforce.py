# NP-Hard issue
#Ref http://www.skorks.com/2011/02/algorithms-a-dropbox-challenge-and-dynamic-programming/
# brute force - exponetial time
'''
Ex: [1, -3, 2, 4]
We need to iterate through the values and on every iteration produce all the possible subsets that
can be made with all the numbers we've looked at up until now. Here is how it looks:

Iteration 1:
[[1]]
Iteration 2:
[[1], [-3], [1, -3]]
Iteration 3:
[[1], [-3], [1, -3], [2], [1, 2], [-3, 2], [1, -3, 2]]
Iteration 4:
[[1], [-3], [1, -3], [2], [1, 2], [-3, 2], [1, -3, 2], [4], [1, 4], [-3, 4], [1, -3, 4],
        [2, 4], [1, 2, 4], [-3, 2, 4], [1, -3, 2, 4]]

there is one small optimization we can make. We can sort our input list before trying to generate the subsets,
this way all the negative values will be first in the list. The implication here is this,
once the sum of any subset exceeds the value we're looking for,
we can instantly discard it since all subsequent values we can append to it will only make it bigger.
'''
def subsets_sum_equal_to(arr, target):
    if len(array) == 0:
        return []

    # initial the subset list
    subsets = []
    for elem in arr:
        if elem == target:
            return [elem]
        else:
            subsets.append([elem])
        for subset in sorted(subsets):
            if sum(subset)+elem == target:
                return subset[:] + [elem]
            elif sum(subset)+elem < target:
                subsets.append(subset[:]+[elem])

    return []



