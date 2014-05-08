
#Given an array of integers (positive and negative) find the largest continuous sum. 


def largestContinuousSum(arr):
  if len(arr) == 0:
    return;
  curSum = largeSum = arr[0];
  for num in arr[1:]:
    curSum = max(curSum+num, num)
    largeSum = max(largeSum, curSum)
    
  return largeSum
