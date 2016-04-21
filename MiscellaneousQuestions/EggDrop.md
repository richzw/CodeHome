Q1:**There is a 100-story building and you are given two eggs. The eggs (and the building) have an interesting property that if you throw the egg from a floor number less than X, it will not break. And it will always break if the floor number is equal or greater than X. Assuming that you can reuse the eggs which didn't break, you need to find X in 
a minimal number of throws. Give an algorithm to find X in minimal number of throws.**

**Approach:**
**A First Try**: Suppose we drop an Marble from the 10th floor, then the 20th, …

- In the first Marble breaks on the first drop (Floor 10), then we have at most 10 drops total.
- If the first Marble breaks on the last drop (Floor 100), then we have at most 19 drops total (floors 1 through 100, then 91 through 99).
- That’s pretty good, but all we’re considered about is the absolute worst case. We should do some “load balancing” to make those two cases more even.

**Goal**: Create a system for dropping Marble1 so that the most drops required is **consistent**, whether Marble1 breaks on the first drop or the last drop.

- A perfectly load balanced system would be one in which Drops of Marble1 + Drops of Marble2 is always the same, regardless of where Marble1 broke.
- For that to be the case, since each drop of Marble1 takes one more step, Marble2 is allowed one fewer step.
- We must, therefore, reduce the number of steps potentially required by Marble2 by one drop each time. For example, if Marble1 is dropped on Floor 20 and then Floor 30, Marble2 is potentially required to take 9 steps. When we drop Marble1 again, we must reduce potential Marble2 steps to only 8. eg, we must drop Marble1 at floor 39.
- We know, therefore, Marble1 must start at Floor X, then go up by X-1 floors, then X-2, …, until it gets to 100.
  Solve for X+(X-1)+(X-2)+…+1 = 100. X(X+1)/2 = 100 -> X = 14

The computer algorithm would be like this. Drop first egg from floors 14, 27, 39, 50, 60, 69, 77, 84, 90, 95, 99, 100... 
(i.e. move up 14 then 13, then 12 floors, etc) until it breaks (or doesn't at 100)

=========
Q2: **With 3 eggs, you could use the extra egg for binary divide-and-conquer.**

Here is my thoughts:

1. Use the first egg to drop from floor 50. The worst case is it will be broken.
2. Now we try with the remaining 2 eggs, for floor 1 to 49, using the same algorithm above.
`N *(N + 1) / 2 > 49`, so `N = 11`. Since we already used one egg in 1), so, the maximum drops would be 12.
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
1). Consider the case that the first drop breaks the egg. Then you can determine the breakfloor if and only if it is at most `f[d-1, e-1]`. Therefore you can't start higher than `f[d-1, e-1] + 1` (and shouldn't start lower, of course).

2). If your first drop doesn't breaks the egg, you are in the case of `f[d-1, e]`, just starting at the floor of your first drop + 1, instead of floor 1.

So, the best you can do is to start dropping eggs at floor `f[d-1, e-1] + 1` (because of (1)), 
and you can get up to `f[d-1, e]` floors higher than that (because of (2)). That's `f[d, e] = f[d-1, e-1] + 1 + f[d-1, e]`

=========
Q4: **Suppose that you have an N-story building and plenty of eggs. An egg breaks if it is dropped from floor T or higher and does not break otherwise. Your goal is to devise a strategy to determine the value of T given the following limitations on the number of eggs and tosses:**
- Version 0: 1 egg, ≤T tosses.
- Version 1: ∼1lgN eggs and ∼1lgN tosses.
- Version 2: ∼lgT eggs and ∼2lgT tosses.
- Version 3: 2 eggs and ∼2N−−√ tosses.
- Version 4: 2 eggs and ≤cT−−√ tosses for some fixed constant c.

**A:**
+ Version 0: sequential search.
+ Version 1: binary search.
+ Version 2: find an interval containing T of size ≤2T, then do binary search.
+ Version 3: find an interval of size N−−√, then do sequential search. Note: can be improved to ∼2N−−−√ tosses.
+ Version 4: 1+2+3+…+t∼12t2. Aim for c=22√.
