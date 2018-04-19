Why  rand()%6 biased?

```c
int x = 7;
while(x > 6) 
    x = 1 + std::rand()/((RAND_MAX + 1u)/6);  // Note: 1+rand()%6 is biased

```

----


There are two issues with rand() % 6 (the 1+ doesn't affect either problem).

First, as several answers have pointed out, if the low bits of rand() aren't appropriately uniform, the result of the
remainder operator is also not uniform.

Second, if the number of distinct values produced by rand() is not a multiple of 6, then the remainder will produce more low
values than high values. That's true even if rand() returns perfectly distributed values.

As an extreme example, pretend that rand() produces uniformly distributed values in the range [0..6]. If you look at the 
remainders for those values, when rand() returns a value in the range [0..5], the remainder produces uniformly distributed
results in the range [0..5]. When rand() returns 6, rand() % 6 returns 0, just as if rand() had returned 0. So you get a 
distribution with twice as many 0's as any other value.

The second is the real problem with rand() % 6.

The way to avoid that problem is to discard values that would produce non-uniform duplicates. You calculate the largest 
multiple of 6 that's less than or equal to RAND_MAX, and whenever rand() returns a value that's greater than or equal to 
that multiple you reject it and call `rand() again, as many times a needed.

So:

```
int max = 6 * ((RAND_MAX + 1u) / 6)
int value = rand();
while (value >= max)
    value = rand();
```

That's a different implementation of the code in question, intended to more clearly show what's going on.

