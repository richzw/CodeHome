"""
I would like to find the highest value m = a*b that satisfies some condition C(m), where 1 <= a <= b <= 1,000,000.
In order to do that, I'd like to iterate all pairs of a,b in decreasing order of a*b.

For example, for values up to 5, the order would be:
5 x 5 = 25
4 x 5 = 20
4 x 4 = 16
3 x 5 = 15
3 x 4 = 12
2 x 5 = 10
3 x 3 = 9
2 x 4 = 8
2 x 3 = 6
1 x 5 = 5
1 x 4 = 4
2 x 2 = 4
1 x 3 = 3
1 x 2 = 2
1 x 1 = 1
So far I've come up with a BFS-like tree search, where I generate candidates from the current "visited" set and
pick the highest value candidate, but it's a tangled mess, and I'm not sure about correctness.
I wonder if there's some sort of trick I'm missing.

I'm also interested in the more general case of ordering by any monotonic function f(a,b), if such a thing exists.

For illustration, C(m) could be "return true if m2+m+41 is prime, otherwise return false", but I'm really looking for 
a general approach.
"""

'''
Provided that C(m) is so magical that you cannot use any better technique to find your solution directly and 
thus you really need to traverse all a*b in decreasing order, this is what I would do:

Initialize a max-heap with all pairs (a, b) such that a = b. This means that the heap contains 
(0, 0), (1, 1), ... , (1.000.000, 1.000.000). The heap should be based on the a * b value.

Now continuously:
Get the max pair (a, b) from the heap.
Verify if (a, b) satisfies C(a * b). If so, you are done.
Otherwise, add (a, b-1) to the heap (provided b > 0, otherwise do nothing).
This is a very simple O(n log n) time and O(n) space algorithm, provided that you find the answer quickly 
(in a few iterations). This of course depends on C.

If you run into space problems you can of course easily decrease the space complexity by splitting up the problem
in a number of subproblems, for instance 2:

Add only (500.000, 500.000), (500.001, 500.001), ... , (1.000.000, 1.000.000) to the heap and 
find your best pair (a, b).
Do the same for (0, 0), (1, 1), ... (499.999, 499.999).
Take the best of the two solutions.
'''
def insert_into_Q((a, b), Q):

    if (a == 0) or (b == 0):
        return

    pos = 0
    for (x, y) in Q:
        if (x == a) and (y == b):
            return
        if x * y < a * b:
            break
        pos = pos + 1
    Q.insert(pos, (a, b))


def main(a, b):

    Q = [(a, b)]
    L = []

    while True:

        if len(Q) == 0:
            break

        (a, b) = Q.pop(0)
        L.append((a, b)) # Replace this with C(a * b) and break if satisfied.

        a1 = a - 1
        b1 = b - 1

        if (a == b):
            insert_into_Q((a1, b), Q)
        else:
            insert_into_Q((a1, b), Q)
            insert_into_Q((a, b1), Q)

    print(L)


if __name__ == "__main__":
    main(5, 5)
