### Question

I am using an int type to store a value. By the semantics of the program, the value always varies in a very small range 
(0 - 36), and int (not a char) is used only because the CPU efficiency.

It seems like that many special arithmetical optimizations can be performed on such a small range of integers. Many function 
calls on those integers might be optimized into a small set of "magical" operations, and some functions may even be optimized 
into table look-ups.

So, is it possible to tell the compiler that this int is always in that small range, and is it possible for the compiler to 
do those optimizations?


### Solution

Yes, it is possible. For example, for gcc you can use `__builtin_unreachable` to tell the compiler about impossible conditions,
like so:

```cpp
if ( value < 0 || value > 36 ) __builtin_unreachable();
```

We can wrap condition above in the macro:

```cpp
#define assume(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)
```

And use it like so:

```cpp
assume(x >= 0 && x <= 10);
```

As you can see, gcc performs optimizations based on this information:

```cpp
#define assume(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)

int func(int x){
  assume(x >=0 && x <= 10);

    if ( x > 11 ){
      return 2;
    }else{
      return 17;
    }
}
```

Produces:

```cpp
func(int):
    mov     eax, 17
    ret
```

One downside, however, that if your code ever breaks such assumptions, you get undefined behavior.
