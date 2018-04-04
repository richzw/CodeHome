**Question**

I am a bit confused by the following code:

```c
#include <iostream>

const char* f()
{
    const char* arr[]={"test"};
    return arr[0];
}

int main()
{
    auto x = f();
    std::cout << x;
}
```

In my opinion, this code should be UB (undefined behaviour). We return a pointer to a C-style array element inside a local
scope. Things should go wrong. However, none of the compilers I tested with complain (I used -Wall -Wextra -pedantic on both 
g++ and clang). valgrind does not complain either.

**Answer**


No, it's not UB.

This:

```c
const char* f()
{
    const char* arr[]={"test"};
    return arr[0];
}
```
Can be rewritten to the equivalent:

```c
const char* f()
{
    const char* arr0 = "test";
    return arr0;
}
```

So we're just returning a local pointer, to a string literal. String literals have static storage duration, nothing dangles.
The function really is the same as:

```c
const char* f()
{
    return "test";
}
```

If you did something like this:

```c
const char* f() {
    const char arr[] = "test"; // local array of char, not array of char const*
    return arr;
}
```

Now that is UB - we're returning a dangling pointer.

