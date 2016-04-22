**Q1:There is a 100-story building and you are given two eggs. The eggs (and the building) have an interesting property that if you throw the egg from a floor number less than X, it will not break. And it will always break if the floor number is equal or greater than X. Assuming that you can reuse the eggs which didn't break, you need to find X in a minimal number of throws. Give an algorithm to find X in minimal number of throws.**

**Approach:**:

**A First Try**: Suppose we drop an egg from the 10th floor, then the 20th, …

- In the first egg breaks on the first drop (Floor 10), then we have at most 10 drops total.
- If the first egg breaks on the last drop (Floor 100), then we have at most 19 drops total (floors 1 through 100, then 91 through 99).
- That’s pretty good, but all we’re considered about is the absolute worst case. We should do some _load balancing_ to make those two cases more even.

**Goal**: Create a system for dropping egg1 so that the most drops required is **consistent**, whether egg1 breaks on the first drop or the last drop.

- A perfectly load balanced system would be one in which `Drops of egg1 + Drops of egg2` is always the same, regardless of where egg1 broke.
- For that to be the case, since each drop of egg1 takes one more step, egg2 is allowed one fewer step.
- We must, therefore, reduce the number of steps potentially required by egg2 by one drop each time. For example, if egg1 is dropped on Floor 20 and then Floor 30, egg2 is potentially required to take 9 steps. When we drop egg1 again, we must reduce potential egg2 steps to only 8. eg, we must drop egg1 at floor 39.
- We know, therefore, egg1 must start at Floor X, then go up by `X-1` floors, then `X-2`, …, until it gets to `100`.
  Solve for `X+(X-1)+(X-2)+…+1 = 100`. `X(X+1)/2 = 100` -> `X = 14`

The computer algorithm would be like this. Drop first egg from floors `14, 27, 39, 50, 60, 69, 77, 84, 90, 95, 99, 100... `
(i.e. move up 14 then 13, then 12 floors, etc) until it breaks (or doesn't at 100)

-----------------------------------------------
**Q2: Suppose that we wish to know which stories in a N-story building are safe to drop eggs from, and which will
cause the eggs to break on landing. We make a few assumptions: An egg that survives a fall can be used again.**

- A broken egg must be discarded.
- The effect of a fall is the same for all eggs.
- If an egg breaks when dropped, then it would break if dropped from a higher window.
- If an egg survives a fall then it would survive a shorter fall.
- It is not ruled out that the first-floor windows break eggs, nor is it ruled out that the Nth-floor windows do not cause an egg to break.

Given an `N` story building and a supply of `d` eggs, ﬁnd the strategy which minimizes (in the worst case) the number of 
experimental drops required to determine the breakﬂoor.

**Answer:** When we drop an egg from a floor `x`, there can be two cases (1) The egg breaks (2) The egg doesn’t break.

- If the egg breaks after dropping from xth floor, then we only need to check for floors lower than `x` with remaining eggs; so the problem reduces to `x-1` floors and `n-1` eggs
- If the egg doesn’t break after dropping from the xth floor, then we only need to check for floors higher than `x`; so the problem reduces to `k-x` floors and `n` eggs.

Since we need to minimize the number of trials in worst case, we take the maximum of two cases. We consider the max of above two cases for every floor and choose the floor which yields minimum number of trials.

```
  k ==> Number of floors
  n ==> Number of Eggs
  eggDrop(n, k) ==> Minimum number of trails needed to find the critical
                    floor in worst case.
  eggDrop(n, k) = 1 + min{max(eggDrop(n - 1, x - 1), eggDrop(n, k - x)): 
                 x in {1, 2, ..., k}}
```                 

Codes

```c
/*
 * Prarams: 
 *     e {int}, the number of eggs
 *     f {int}, the number of floors
 * Return:
 *     {int}, the worst number of trails in the worst case 
*/
int max(int a, int b) { return a > b ? a : b; }
int eggDrop(int e, int f) {
	// edge cases: no floor, one floor, or one egg
	if (f == 0 || f == 1 || e == 1)
		return f;

	int min = INT_MAX;
	int res = 0;
	for (int idx = 1; idx <= f; ++idx) {
		res = max(eggDrop(e - 1, idx - 1), eggDrop(e, f - idx));
		if (res < min)
			min = res;
	}

	return min + 1; // Fixme: plus 1
}

// Dynamic Programming solution
int eggDropDP(int e, int f) {
	// create the dp array
	int** eggFloor;
	eggFloor = new int*[e + 1];
	for (int i = 0; i < e + 1; ++i) {
		eggFloor[i] = new int[f + 1];
	}

	// initialize the dp array
	// case: zero floor, one floor
	for (int i = 0; i < e + 1; ++i) {
		eggFloor[i][0] = 0;
		eggFloor[i][1] = 1;
	}
	// case: zero egg, one egg
	for (int j = 0; j < f; ++j) {
		eggFloor[0][j] = 0;
		eggFloor[1][j] = j;
	}

	for (int i = 2; i < e + 1; ++i) {
		for (int j = 2; j < f + 1; ++j) {
			eggFloor[i][j] = INT_MAX;
			int res = 0;
			for (int idx = 1; idx <= j; ++idx)
			{
				res = 1 + max(eggFloor[i - 1][idx - 1], eggFloor[i][j - idx]);
				if (res < eggFloor[i][j])
					eggFloor[i][j] = res;
			}
		}
	}

	for (int i = 0; i < e + 1; ++i) {
		delete eggFloor[i];
	}
	delete eggFloor;

	return eggFloor[e][f];
}
```

-----------------------------------------------------------------
**Q3: Suppose that you have an N-story building and plenty of eggs. An egg breaks if it is dropped from floor T or higher and does not break otherwise. Your goal is to devise a strategy to determine the value of T given the following limitations on the number of eggs and tosses:**
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
