import random
"""
N-queens problem

solve 8 queens problem with generator method - brute force
"""

def conflict(state, nextX):
    """(tuple, int) -> bool

    Return whether the current position can be put one queen or not

    >>> conflict((1,3,0), 1)
    False
    >>> conflict((1,3,0), 2)
    True
    """
    nextY = len(state)
    for i in xrange(nextY):
        if abs(state[i] - nextX) in (0, nextY - i):
            return True
    return False

def queens(num=8, state=()):
    """(int, tuple) -> tuple

    Return the list of the N queens position

    >>> list(queen(3))
    []
    >>> list(queen(4))
    [(1, 3, 0, 2), (2, 0, 3, 1)]
    """
    for pos in xrange(num):
        if not conflict(state, pos):
            if len(state) == num - 1:
                yield (pos,)
            else:
                for result in queens(num, state+(pos,)):
                    yield (pos,)+result


def pretty_print(solution):
    """
    
    """
    def line(pos, length=len(solution)):
        return '- ' * pos + 'X ' + '- ' * (length - pos - 1)
    for pos in solution:
        print line(pos)

if __name__ == '__main__':
    pretty_print(random.choice(list(queens(8))))
