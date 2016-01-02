'''
For instance, I have lists:

a[0] = [1, 1, 1, 0, 0]
a[1] = [1, 1, 0, 0, 1]
a[2] = [0, 1, 1, 1, 0]
# and so on

They seem to be different, but if it is supposed that the start and the end are connected, then they are circularly identical.
'''

def isCircular(arr1, arr2):
    if len(arr1) != len(arr2):
        return False

    str1 = ' '.join(map(str, arr1))
    str2 = ' '.join(map(str, arr2))
    if len(str1) != len(str2):
        return False

    return str1 in str2 + ' ' + str2

from random import random
bigList = [int(1000 * random()) for i in xrange(10**6)]
bigList2 = bigList[:]
bigList2.append(bigList2.pop(0))

# then test how much time will it take to come up with an answer
from datetime import datetime
startTime = datetime.now()
print isCircular(bigList, bigList2)
print datetime.now() - startTime    # please fill free to use timeit, but it will give similar results    
