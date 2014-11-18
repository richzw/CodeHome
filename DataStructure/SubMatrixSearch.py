"""
I give quotation mark because what I mean is for example:

B = [[1,2,3,4,5],
     [6,7,8,9,10],
     [11,12,13,14,15],
     [16,17,18,19,20]]
suppose we select row 2,4 and col 1,3, the intersections will give us

A = [[6,8],
     [16,18]]
My question is suppose I have A and B, is there a way that I can find out which rows and cols are selected from B to give A?

"""

'''
This is a very hard combinatorial problem. In fact the Subgraph Isomorphism Problem can be reduced to your problem
(in case the matrix A only has 0-1 entries, your problem is exactly a subgraph isomorphism problem). 
This problem is known to be NP-complete.

Here is a recursive backtracking solution which does a bit better than brute-forcing all possible solutions. 
Note that this still takes exponential time in the worst case. However, if you assume that a solution exists and
that there are no ambiguities (for example that all the entries in B are distinct), this finds the solution in linear time.
'''
def locate_columns(a, b, offset=0):
    """Locate `a` as a sublist of `b`.

    Yields all possible lists of `len(a)` indices such that `a` can be read
    from `b` at those indices.
    """
    if not a:
        yield []
    else:
        positions = (offset + i for (i, e) in enumerate(b[offset:])
                     if e == a[0])
        for position in positions:
            for tail_cols in locate_columns(a[1:], b, position + 1):
                yield [position] + tail_cols


def locate_submatrix(a, b, offset=0, cols=None):
    """Locate `a` as a submatrix of `b`.

    Yields all possible pairs of (row_indices, column_indices) such that
    `a` is the projection of `b` on those indices.
    """
    if not a:
        yield [], cols
    else:
        for j, row in enumerate(b[offset:]):
            if cols:
                if all(e == f for e, f in zip(a[0], [row[c] for c in cols])):
                    for r, c in locate_submatrix(a[1:], b, offset + j + 1, cols):
                        yield [offset + j] + r, c
            else:
                for cols in locate_columns(a[0], row):
                    for r, c in locate_submatrix(a[1:], b, offset + j + 1, cols):
                        yield [offset + j] + r, c

B = [[1,2,3,4,5], [6,7,8,9,10], [11,12,13,14,15], [16,17,18,19,20]]
A = [[6,8], [16,18]]

for loc in locate_submatrix(A, B):
    print loc
