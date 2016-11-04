### Question

NULL is often used in the context of pointers, and is defined via macros in multiple standard libraries (such as <iostream>)
to be the integer 0. '\0' is the null character, and is 8 bits of zeros. Incidentally, 8 bits of zeros is equivalent to the 
integer 0.

In some cases, although it is considered to be horrible style, these two can be interchanged:

```cpp
int *p='\0';
if (p==NULL) //evaluates to true
    cout << "equal\n";
```

Or

```cpp
char a=NULL;
char b='\0';
if (a==b) //evaluates to true
    cout << "equal again\n";
```

### Answer

This code defines several overloads of a single function. Each overload outputs the type of the parameter:

```cpp
#include <iostream>

void f(int) {
    std::cout << "int" << std::endl;
}

void f(long) {
    std::cout << "long" << std::endl;
}

void f(char) {
    std::cout << "char" << std::endl;
}

void f(void*) {
    std::cout << "void*" << std::endl;
}

int main() {
    f(0);
    f(NULL);
    f('\0');
    f(nullptr);
}
```

On Ideone this outputs

```
int
int
char
void*
```

Therefore I would claim that the problem with overloads is not an actual application but a pathological case. 
The `NULL` constant will behave wrong anyway, and should be replaced with `nullptr` in C++11.

**What if NULL is not zero?**

> Note that what is a null pointer in the C language. It does not matter on the underlying architecture. If the underlying 
architecture has a null pointer value defined as address `0xDEADBEEF`, then it is up to the compiler to sort this mess out.

> As such, even on this funny architecture, the following ways are still valid ways to check for a null pointer:

```
if (!pointer)
if (pointer == NULL)
if (pointer == 0)
```

> The following are INVALID ways to check for a null pointer:

```
#define MYNULL (void *) 0xDEADBEEF
if (pointer == MYNULL)
if (pointer == 0xDEADBEEF)
```

> as these are seen by a compiler as normal comparisons.

**Summary**

All in all, I would say that the differences are mostly stylistic. If you have a function that takes int and overload that 
takes char, and they function differently, you will notice difference when you call them with \0 and NULL constants. 
But as soon as you place those constants in variables, the difference disappears, because the function that is called is 
deducted from the type of the variable.

Using correct constants makes the code more maintainable, and conveys meaning better. You should use `0` when you mean a 
number, \0 when you mean a character, and nullptr when you mean a pointer. But to answer your question, there is not really 
an actual use case that would prevent you from using \0 and NULL interchangeably.
