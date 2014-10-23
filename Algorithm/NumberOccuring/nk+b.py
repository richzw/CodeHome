"""
Given an Array of size (n*k+b) where n elements occur k times and one element occurs b times, 
in other words there are n+1 distinct Elements. Given that 0 < b < k find the element occurring b times.

My Attempted solutions
    Obvious solution will be using hashing but it will not work if the numbers are very large. Complexity is O(n)

    Using map to store the frequencies of each element and then traversing map to find the element occurring b times.
    As Map's are implemented as height balanced trees Complexity will be O(nlogn).

"""

'''
To guess i-th bit of answer, follow this procedure:
    Count how many numbers in array has i-th bit set, store as cnt
    If cnt % k is non-zero, then i-th bit of answer is set. Otherwise it is clear.

'''
from random import randint, shuffle

def generate_test_data(n, k, b):
    k_rep = [randint(0, 1000) for i in xrange(n)]
    b_rep = [randint(0, 1000)]
    numbers = k_rep*k + b_rep*b
    shuffle(numbers)
    print "k_rep: ", k_rep
    print "b_rep: ", b_rep
    return numbers

def solve(data, k):
    cnts = [0]*10
    for number in data:
        bits = [number >> b & 1 for b in xrange(10)]
        cnts = [cnts[i] + bits[i] for i in xrange(10)]
    return reduce(lambda a,b:2*a+(b%k>0), reversed(cnts), 0)

print "Answer: ", solve(generate_test_data(10, 15, 13), 3)
