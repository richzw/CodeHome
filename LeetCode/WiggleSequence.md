
### Question

A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and 
negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a 
wiggle sequence.

For example, `[1,7,4,9,2,5]` is a wiggle sequence because the differences `(6,-3,5,-7,3)` are alternately positive and negative. 
In contrast, `[1,4,7,2,5]` and `[1,7,4,5,5]` are not wiggle sequences, the first because its first two differences are positive and 
the second because its last difference is zero.

### Solution 1

Brute Force (recursive)

```c
int calc(int* num, int len, int idx, bool isUp) {
	int maxCnt = 0;

	for (int i = idx + 1; i < len; ++i) {
		if ((isUp && num[i] > num[idx]) || (!isUp && num[i] < num[idx]))
			maxCnt = max(maxCnt, 1 + calc(num, len, i, !isUp));
	}

	return maxCnt;
}

int wiggleMaxLen(int* nums, int len) {
	if (len < 2)
		return len;
	return 1 + max(calc(nums, len, 0, true), calc(nums, len, 0, false));
}
```

### solution 2

```c
int wiggleMax(int* nums, int len) {
	if (len < 2)
		return len;

	int down = 1, up = 1;
	for (int i = 1; i < len; ++i) {
		if (nums[i] > nums[i - 1])
			up = down + 1;
		else if (nums[i] < nums[i - 1])
			down = up + 1;
	}

	return max(up, down);
}
```
