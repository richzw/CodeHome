### Question

Adding two 32-bit integers can result an integer overflow:

```c
uint64_t u64_z = u32_x + u32_y;
```

This overflow can be avoided if one of the 32-bit integers is first casted or added to a 64-bit integer.

```c
uint64_t u64_z = u32_x + u64_a + u32_y;
```

However, if the compiler decides to reorder the addition:

```c
uint64_t u64_z = u32_x + u32_y + u64_a;
```

the integer overflow might still happen.

Are compilers allowed to do such a reordering or can we trust them to notice the result inconsistency and keep the expression order as is?


### Answer

If the optimiser does such a reordering it is still bound to the C specification, so such a reordering would become:

```c
uint64_t u64_z = (uint64_t)u32_x + (uint64_t)u32_y + u64_a;
```

Rationale:

We start with

```c
uint64_t u64_z = u32_x + u64_a + u32_y;
```

Addition is performed left-to-right.

The integer promotion rules state that in the first addition in the original expression, `u32_x` be promoted to uint64_t. 
In the second addition, `u32_y` will also be promoted to `uint64_t`.

So, in order to be compliant with the C specification, any optimiser must promote u32_x and u32_y to 64 bit unsigned values.
This is equivalent to adding a cast.

------------------------------------------------------------------

There is the "as if" rule in C, C++, and Objective-C: The compiler may do whatever it likes as long as no conforming program can tell the difference.

In these languages, a + b + c is defined to be the same as (a + b) + c. If you can tell the difference between this and for example a + (b + c) then the compiler cannot change the order. If you can't tell the difference, then the compiler is free to change the order, but that's fine, because you can't tell the difference.

In your example, with b = 64 bit, a and c 32 bit, the compiler would be allowed to evaluate (b + a) + c or even (b + c) + a, because you couldn't tell the difference, but not (a + c) + b because you can tell the difference.

In other words, the compiler isn't allowed to do anything that makes your code behave different from what it should. It is not required to produce the code that you think it would produce, or that you think it should produce, but the code will give you exactly the results it should.

### Source

http://stackoverflow.com/questions/38563707/a-b-c-%E2%89%A0-a-c-b-and-compiler-reordering
