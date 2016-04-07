
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

