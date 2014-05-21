'''
Just like with any dynamic programming problem, we need to produce a matrix, the key is to figure out what it's a matrix of
(how do we label the rows and how do we label the columns). In this case the rows are simply the indexes of our input array; 
the columns are labelled with every possible sum that can be made out of the input numbers.
In our case, the smallest sum we can make from our input is -3 since that's the only negative number we have, 
the biggest sum is seven (1 + 2 + 4). So, our uninitialized matrix looks like this:

+---+----+----+----+---+---+---+---+---+---+---+---+
|   | -3 | -2 | -1 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
+---+----+----+----+---+---+---+---+---+---+---+---+
| 0 |    |    |    |   |   |   |   |   |   |   |   |
| 1 |    |    |    |   |   |   |   |   |   |   |   |
| 2 |    |    |    |   |   |   |   |   |   |   |   |
| 3 |    |    |    |   |   |   |   |   |   |   |   |
+---+----+----+----+---+---+---+---+---+---+---+---+
So far so good, but what should we put in every cell of our matrix. In this case every cell will contain either
T (true) or F (false).

A T value in a cell means that the sum that the column is labelled with can be constructed
using the input array numbers that are indexed by the current row label and the labels of all the previous rows
we have already looked at.

There are three patterns that are starting to emerge.
1.For every row, the column which is equivalent to the number indexed by the row get a T in it
(e.g. row zero represents the number 1, so the column labelled by 1 gets a T in row 0,
row one represents the number -3 so the column labelled by -3 get a T in row 1 etc.),
every row will get one T in one of the columns via this pattern. This is because a single number by itself is a valid subset sum.

2.If a column already has a T in the previous row, this T propagates down to the current row
(e.g. when looking at the second row, the column labelled by 1 has a T in the first row and will therefore have
a T in the second row also, when looking at the third row columns labelled by -3, -2 and 1 all had a T
in the second row and will therefore contain a T in the third row).
This is due to the fact that once it is possible to construct a certain sum using a subset of our input numbers,
looking at more of the input numbers does not invalidate the existing subsets.

3.Looking at any column label X in the current row which still has a value of F,
if we subtract the number indexed by the current row from this column label we get a new number Y,
we then check the row above the current row in the column labelled by Y, if we see a T,
this T is propagated into the column X in the current row (e.g. if we're looking at the second row,
column labelled with -2, we subtract the number of the current row -3 from the column label, -2 – -3 = -2 + 3 = 1,
this new number is the column label in the first row, we can see that in the first row in the column labelled
with 1 there is a T, therefore this T gets propagated to the second row into the column labelled with -2).
This is due to the fact that if we take a sum that is already possible and add another number to it,
this obviously creates a new sum which is now possible.

+---+----+----+----+---+---+---+---+---+---+---+---+
|   | -3 | -2 | -1 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
+---+----+----+----+---+---+---+---+---+---+---+---+
| 0 | F  | F  | F  | F | T | F | F | F | F | F | F |
| 1 | T  | T  | F  | F | T | F | F | F | F | F | F |
| 2 | T  | T  | T  | T | T | T | T | F | F | F | F |
| 3 | T  | T  | T  | T | T | T | T | T | T | T | T |
+---+----+----+----+---+---+---+---+---+---+---+---+
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
