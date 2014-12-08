'''
F(0) = 0
F(1) = 1
F(2) = 2
F(2*n) = F(n) + F(n+1) + n , n > 1
F(2*n+1) = F(n-1) + F(n) + 1, n >= 1

I am given a number n < 10^25 and I have to show that exists a value a such as F(a)=n. Because of how the function is defined, 
there might exist a n such as F(a)=F(b)=n where a < b and in this situation I must return b and not a
'''

class Memoize:
    def __init__(self, fn):
        self.fn = fn
        self.memo = {}
    def __call__(self, *args):
        if not self.memo.has_key(args):
            self.memo[args] = self.fn(*args)
        return self.memo[args]

@Memoize
def R(n):
    if n<=1: return 1
    if n==2: return 2
    n,rem = divmod(n,2)
    if rem:
        return R(n)+R(n-1)+1
    return R(n)+R(n+1)+n
