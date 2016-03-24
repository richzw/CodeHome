
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
