
### Question
I've seen programmers use the formula

```
mid = start + (end - start) / 2
```

instead of using the simpler formula

```
mid = (start + end) / 2
```

for finding the middle element in the array or list. Why do they use the former one?

### Answer

There are three reasons.

First of all, `start + (end - start) / 2` works even if you are using `pointers`.

```c
int *start = ..., *end = ...;
int *mid = start + (end - start) / 2; // works as expected
int *mid = (start + end) / 2;         // type error, won't compile
```

Second of all, `start + (end - start) / 2` won't overflow if start and end are large. With signed operands, overflow is `undefined`:

```c
int start = 0x7ffffffe, end = 0x7fffffff;
int mid = start + (end - start) / 2; // works as expected
int mid = (start + end) / 2;         // overflow... undefined
```

(Note that end - start may also overflow, but only if start < 0 or end < 0.)

Or with unsigned arithmetic, overflow is defined but gives you the wrong answer:

```c
unsigned start = 0xfffffffeu, end = 0xffffffffu;
unsigned mid = start + (end - start) / 2; // works as expected
unsigned mid = (start + end) / 2;         // mid = 0x7ffffffe
```

Finally, you often want to round towards the start element.

```c
int start = -3, end = 0;
int mid = start + (end - start) / 2; // -2, closer to start
int mid = (start + end) / 2;         // -1, surprise!
```

