Q1:**There is a 100-story building and you are given two eggs. The eggs (and the building) have an interesting property that if you throw the egg from a floor number less than X, it will not break. And it will always break if the floor number is equal or greater than X. Assuming that you can reuse the eggs which didn't break, you need to find X in 
a minimal number of throws. Give an algorithm to find X in minimal number of throws.**

**A:**
the whole question grinds up to how to make use of the first egg to reduce the linear testing using the second egg.
This problem can be solved by thinking backwards from the answer. So, here are the steps:
1. Take N for the answer
2. The best choice will be to start with floor N first.
- if the egg breaks, do a linear search starting from 1 to N-1, guaranteeing a solution in N attempts.
- else go to N + (N-1) floor.
3. Continuing in this way, with N attempts, we can cover sum(N + N-1 + N-2... 2 + 1) floors.
Thus we will need to cover 100 floors, so N *(N + 1) / 2 > 100
N = 14, so the answer is 14 maximum drops and we can find the floor.

The computer algorithm would be like this. Drop first egg from floors 14, 27, 39, 50, 60, 69, 77, 84, 90, 95, 99, 100... 
(i.e. move up 14 then 13, then 12 floors, etc) until it breaks (or doesn't at 100)

=========
Q2: **With 3 eggs, you could use the extra egg for binary divide-and-conquer.** Here is my thoughts:

1. Use the first egg to drop from floor 50. The worst case is it will be broken.
2. Now we try with the remaining 2 eggs, for floor 1 to 49, using the same algorithm above.
N *(N + 1) / 2 > 49, so N = 11. Since we already used one egg in 1), so, the maximum drops would be 12.
So, with 3 eggs, it is slightly better than 2 eggs. It seems there is a diminishing return on using more eggs.
Overall, in terms of solving a computer science problem, certain optimization is better, but too much would be overkill.


=========
Q3:**Suppose that we wish to know which stories in a N-story building are safe to drop eggs from, and which will
cause the eggs to break on landing. We make a few assumptions: An egg that survives a fall can be used again.**
- A broken egg must be discarded.
- The effect of a fall is the same for all eggs.
- If an egg breaks when dropped, then it would break if dropped from a higher window.
- If an egg survives a fall then it would survive a shorter fall.
- It is not ruled out that the first-floor windows break eggs, nor is it ruled out that the Nth-floor windows do not cause an egg to break.

Given an N story building and a supply of d eggs, ﬁnd the strategy which minimizes (in the worst case) the number of 
experimental drops required to determine the breakﬂoor.

**A:**
1. Consider the case that the first drop breaks the egg. Then you can determine the breakfloor if and 
only if it is at most f[d-1, e-1]. Therefore you can't start higher than `f[d-1, e-1] + 1`
(and shouldn't start lower, of course).

2. If your first drop doesn't breaks the egg, you are in the case of `f[d-1, e]`, just starting at the floor of 
your first drop + 1, instead of floor 1.

So, the best you can do is to start dropping eggs at floor `f[d-1, e-1] + 1` (because of (1)), 
and you can get up to `f[d-1, e]` floors higher than that (because of (2)). That's
`f[d, e] = f[d-1, e-1] + 1 + f[d-1, e]`

