
Q: How to ask, programmatically, a compiler to compile a file in C++

A:

```c
#include <cstdlib>
#include <fstream>

// Use raw string literal for easy coding
auto prog = R"~(

#include <iostream>

int main()
{
    std::cout << "Hello World!" << '\n';
}

)~"; // raw string literal stops here

int main()
{
    // save program to disk
    std::ofstream("prog.cpp") << prog;

    std::system("g++ -o prog prog.cpp"); // compile
    std::system("./prog"); // run
}
```

----------------------------------------------------------

Array in Cpp

```c++
int* p = new int[s];  // allocated array, p has type int*
int q[10];            // declared array, q has type int[10]
std::vector<int> u;   // has member allocated array
std::array<int, 5> v; // has member declared array
```

The differentiation is not based on stack/heap. A _declared array_ can be heap allocated (e.g. `new array<int,5>`) or not on the stack (e.g. `static double x[100];`)

With an _allocated array_, the size does not have to be a constant expression. The size will simply be encoded into the block of memory yielded by the allocator somehow (for instance the four leading bytes before the actual data starts) so that the corresponding `delete[]` knows how many elements to delete.

With a _declared array_ (or _non-allocated array_, no `new/malloc/`etc.), the size must† be coded into the type, so that the destructor knows what to do. The only allowed, standard array declaration is:

`T D[constant-expression_opt];`

(where D is a declarator that could be a name or another array declaration, etc.) Declared arrays are not limited to the stack. Note that, for added confusion, the constant-expression is optional.
