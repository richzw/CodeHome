// https://en.wikipedia.org/wiki/Digraphs_and_trigraphs
// 

```c
#include <stdio.h>
#define M(a,b) a%:%:b  

main()
{
  int a=1, b=2, ab[]={10,20}, c;
  printf( "%d", M(a,b)<:a:> );
  printf( "%d", M(a,b)<:a:>?a:b );
  printf( "%d", c=M(a,b)<:a:>?a:b );
}
```

Will be parsed as below through bigraph

```c
#define M(a,b) a##b

main()
{
  int a=1, b=2, ab[]={10,20}, c;
  printf( "%d", M(a,b)[a] );
  printf( "%d", M(a,b)[a]?a:b );
  printf( "%d", c=M(a,b)[a]?a:b );
}
```

```c
main()
{
  int a=1, b=2, ab[]={10,20}, c;
  printf( "%d", ab[a] );
  printf( "%d", ab[a]?a:b );
  printf( "%d", c=ab[a]?a:b );
}
```

```c
main()
{
  int a=1, b=2, ab[]={10,20};
  printf( "%d", ab[a] );
  printf( "%d", ab[a]?a:b );
  printf( "%d", ab[a]?a:b );
}
```
