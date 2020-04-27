https://stackoverflow.com/questions/61411498/why-does-rand-repeat-numbers-far-more-often-on-linux-than-mac

Another thing that appears surprising at first glance is how the macOS rand() can manage to avoid duplicates so well. Looking at its source code, we find the implementation to be as follows:

```c
/*
 * Compute x = (7^5 * x) mod (2^31 - 1)
 * without overflowing 31 bits:
 *      (2^31 - 1) = 127773 * (7^5) + 2836
 * From "Random number generators: good ones are hard to find",
 * Park and Miller, Communications of the ACM, vol. 31, no. 10,
 * October 1988, p. 1195.
 */
    long hi, lo, x;

    /* Can't be initialized with 0, so use another value. */
    if (*ctx == 0)
        *ctx = 123459876;
    hi = *ctx / 127773;
    lo = *ctx % 127773;
    x = 16807 * lo - 2836 * hi;
    if (x < 0)
        x += 0x7fffffff;
    return ((*ctx = x) % ((unsigned long) RAND_MAX + 1));
```

This does indeed result in all numbers between 1 and RAND_MAX, inclusive, exactly once, before the sequence repeats again. Since the next state is based on multiplication, the state can never be zero (or all future states would also be zero). Thus the repeated number you see is the first one, and zero is the one that is never returned.

Apple has been promoting the use of better random number generators in their documentation and examples for at least as long as macOS (or OS X) has existed, so the quality of rand() is probably not deemed important, and they've just stuck with one of the simplest pseudorandom generators available. (As you noted, their rand() is even commented with a recommendation to use arc4random() instead.)

On a related note, the simplest pseudorandom number generator I could find that produces decent results in this (and many other) tests for randomness is xorshift*:

```c
uint64_t x = *ctx;
x ^= x >> 12;
x ^= x << 25;
x ^= x >> 27;
*ctx = x;
return (x * 0x2545F4914F6CDD1DUL) >> 33;
```

This implementation results in almost exactly 790 million duplicates in your test.
