#Ref: http://stackoverflow.com/questions/9442958/find-the-element-occurring-b-times-in-an-an-array-of-size-nkb?rq=1

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

'''
Method 2

I assume:
    The elements of the array are comparable.
    We know the values of n and k beforehand.
    A solution O(n*k+b) is good enough.

Let the number occuring only b times be S. We are trying to find the S in an array of n*k+b size.

Recursive Step: Find the median element of the current array slice as in Quick Sort in lineer time. 
Let the median element be M.

After the recursive step you have an array where all elements smaller than M occur on the left of the first occurence 
of M. All M elements are next to each other and all element larger than M are on the right of all occurences of M.

Look at the index of the leftmost M and calculate whether S<M or S>=M. Recurse either on the left slice or the right 
slice.

So you are doing a quick sort but delving only one part of the divisions at any time. You will recurse O(logN) times
but each time with 1/2, 1/4, 1/8, .. sizes of the original array, so the total time will still be O(n).

Clarification: Let's say n=20 and k = 10. Then, there are 21 distinct elements in the array, 
20 of which occur 10 times and the last occur let's say 7 times. I find the medium element, 
let's say it is 1111. If the S<1111 than the index of the leftmost occurence of 1111 will be less than 11*10. 
If S>=1111 then the index will be equal to 11*10.

Full example: n = 4. k = 3. Array = {1,2,3,4,5,1,2,3,4,5,1,2,3,5} After the first recursive step 
I find the median element is 3 and the array is something like: {1,2,1,2,1,2,3,3,3,5,4,5,5,4} 
There are 6 elements on the left of 3. 6 is a multiple of k=3. So each element must be occuring 3 times there. 
So S>=3. Recurse on the right side. And so on.

'''
