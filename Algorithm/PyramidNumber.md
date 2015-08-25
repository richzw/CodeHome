
> Given a number of bricks, output the total number of 2d pyramids possible, where a pyramid is defined as any structure 
> where a row of bricks has strictly less bricks than the row below it. You do not have to use all the bricks.

```
example, n = 6, number of pyramids is 13.

X

XX

X
XX   XXX

X
XXX   XXXX

XX      X
XXX   XXXX   XXXXX

X
XX      XX       X
XXX   XXXX   XXXXX   XXXXXX
```

**Solution 1**

Let's choose a suitable definition:

`f(n, m) = # pyramids out of n bricks with base of size < m`
The answer you are looking for now is (given that N is your input number of bricks):

`f(N, N+1) - 1`
Let's break that down:

- The first `N` is obvious: that's your number of bricks.
- Your bottom row will contain at most `N` bricks (because that's all you have), so `N+1` is a sufficient upper bound.
- Finally, the `- 1` is there because technically the empty pyramid is also a pyramid (and will thus be counted) 
but you exclude that from your solutions. The base cases are simple:

```
f(n, 0) = 1   for any n >= 0
f(0, m) = 1   for any m >= 0
```

In both cases, it's the empty pyramid that we are counting here.

------------------------------------

Now, all we need still is a recursive formula for the general case.

Let's assume we are given `n` and `m` and choose to have `i` bricks on the bottom layer. What can we place on top of this layer? 
A smaller pyramid, for which we have `n - i` bricks left and whose base has size `< i`. This is exactly `f(n - i, i)`.

What is the range for `i`? We can choose an empty row so `i >= 0`. Obviously, `i <= n` because we have only `n` bricks.
But also, `i <= m - 1`, by definition of `m`.

This leads to the recursive expression:

`f(n, m) = sum f(n - i, i) for 0 <= i <= min(n, m - 1)`

-----------------

You can compute f recursively, but using dynamic programming it will be faster of course. 
Storing the results matrix is straightforward though, so I leave that up to you.

**Solution 2**

Since we are asked to count pyramids of any cardinality less than or equal to n, we may consider each cardinality in turn 
(pyramids of 1 element, 2 elements, 3...etc.) and sum them up. But in how many different ways can we compose a pyramid
from k elements? The same number as the count of distinct partitions of k 
(for example, for k = 6, we can have (6), (1,5), (2,4), and (1,2,3)). 
A generating function/recurrence for the count of distinct partitions is described in Wikipedia and a sequence at OEIS.

Recurrence, based on the _Pentagonal number Theorem_:

```javscript
function numPyramids(n){

  var distinctPartitions = [1,1],
      pentagonals = {},
      m = _m = 1,
      pentagonal_m = 2,
      result = 1;

  while (pentagonal_m / 2 <= n){
    pentagonals[pentagonal_m] = Math.abs(_m);
    m++;
    _m = m % 2 == 0 ? -m / 2 : Math.ceil(m / 2);
    pentagonal_m = _m * (3 * _m - 1);
  }

  for (var k=2; k<=n; k++){
    distinctPartitions[k] = pentagonals[k] ? Math.pow(-1,pentagonals[k]) : 0;
    var cs = [1,1,-1,-1],
        c = 0;
    for (var i in pentagonals){
      if (i / 2 > k)
        break;
      distinctPartitions[k] += cs[c]*distinctPartitions[k - i / 2];
      c = c == 3 ? 0 : c + 1;
    }
    result += distinctPartitions[k];
  }
  return result;
}

console.log(numPyramids(6)); // 13
```
