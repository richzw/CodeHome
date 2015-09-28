
-----------------------

Q: Given the code below, how would you create/implement SR.h 
so that it produces the correct output WITHOUT any asterisks in your solution?

```c
#include <cstdio>
#include "SR.h"

int main()
{
    int j = 5;
    int a[] = {10, 15};
    {
        SR x(j), y(a[0]), z(a[1]);

        j = a[0];
        a[0] = a[1];
        a[1] = j;

        printf("j = %d, a = {%d, %d}\n", j, a[0], a[1]);
    }

    printf("j = %d, a = {%d, %d}\n", j, a[0], a[1]);
}
```

Output:

```
j = 10, a = {15, 10}
j = 5, a = {10, 15}
```

A:

```c
class SR
{
public:
  SR(int& var) : capture(var), value(var) {}
  ~SR() { capture = value; }

private:
  int& capture;
  int value;
};
```



--------------------------------

