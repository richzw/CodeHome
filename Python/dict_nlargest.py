import heapq

seq = [100, 2, 400, 500, 400]

def a(seq):
    """returns [(3, 500), (2, 400)]"""
    return heapq.nlargest(2, enumerate(seq), key=lambda x: x[1])

def b(seq):
    """returns [3, 2]"""
    return map(seq.index, heapq.nlargest(2, seq))

def c(seq):
    """returns [(500, 3), (400, 2)]"""
map(lambda n: (n, seq.index(n)), heapq.nlargest(2, seq))


#-----------------------------------------------------------------------------
def dict_nlargest(d,n):
    return heapq.nlargest(n ,d, key = lambda k: d[k])

d = { 'a':10.0, 'b':2.0, 'c':5.0, 'd':3.0, 'e':15.0 }
print dict_nlargest(d,3)


#-----------------------------------------------------------------------------
class Toy:
    def __init__Toy(self, s, i, f):
        self.s = s
        self.i = i
        self.f = f

l = [ Toy('a', 10, 4.4), Toy('b', 4, 12.0),
      Toy('c', 2, 20.0), Toy('d', 1, 5.0) ]

# largest by the 'f' attribute
print heapq.nlargest(2, l, key = lambda o: o.f)

# largest by the 'i' attribute
print heapq.nlargest(2, l, key = lambda o: o.i)

