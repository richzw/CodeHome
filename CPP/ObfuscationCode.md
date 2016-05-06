
-----------------------------------------

**Q**: Does this codes call `main` directly?

```c
#include <stdio.h>
#define decode(s,t,u,m,p,e,d) m##s##u##t
#define begin decode(a,n,i,m,a,t,e)

int begin()
{
  printf("Ha HA see how it is?? ");
}
```

**A**: 
No program relying only on the features of standard C can run without `main` function. 
`main` is hidden in the preprocessor defined. `begin()` will expand to `decode(a,n,i,m,a,t,e)` which further will be expanded to `main`.

`int begin() -> int decode(a,n,i,m,a,t,e)() -> int m##a##i##n() -> int main()`

----------------------------------------------------

**Q**: What does MACRO + 0 mean?

```c
#if SOMETHING_SUPPORTED+0 != 0
...
#endif
```

**A**:

`#if X+0 != 0` is different to `#if X` in the case where `X` is defined to empty (note: this is different to the case of `X` not being defined), e.g.:

```c
#define X

#if X          // error
#if X+0 != 0   // no error; test fails
```

It is very common to define empty macros: project configuration may generate some common header that contains a bunch of lines `#define USE_FOO`, `#define USE_BAR` to enable features that the system supports, and so on.

The `!= 0` is redundant, the code could have just been `#if X+0`.

```
X       #if X     #if X+0 != 0
<undef> false     false
<empty> error     false
0       false     false
1       true      true
2       true      true
a       false     false
xyz     false     false
12a     error     error
12 a    error     error
```
