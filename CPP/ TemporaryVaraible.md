### Question

Why does the following code crash both on Visual Studio and GCC?

For it to crash it requires the range-based for loop, std::map, std::string and taking a reference to the string. If I remove any one of them it will work.

```c++
#include <iostream>
#include <string>
#include <map>
using namespace std;

struct S
{
    map<string, string> m;

    S()
    {
        m["key"] = "b";
    }

    const string &func() const
    {
        return m.find("key")->second;
    }
};

int main()
{
    for (char c : S().func())
        cout << c;

    return 0;
}
```

### Anwser

The range initialization line of a `for(:)` loop does not extend lifetime of anything but the final temporary (if any).
Any other temporaries are discarded prior to the `for(:)` loop executing.

Now, do not despair; there is an easy fix to this problem. But first a walk through of what is going wrong.

The code `for(auto x:exp){ /* code */ }` expands to, basically:

```cpp
{
  auto&& __range=exp;
  auto __it=std::begin(__range);
  auto __end=std::end(__range);
  for(; __it!=__end;++__it){
    auto x=*__it;
    /* code */
  }
}
```

(With a modest lies on the __it and __end lines, and all variables starting with __ have no visible name. 
Also I am showing C++17 version, because I believe in a better world, and the differences do not matter here.)

Your exp creates a temporary object, then returns a reference to within it. The temporary dies after that line, 
so you have a dangling reference in the rest of the code.

Fixing it is relatively easy. To fix it:

```cpp
std::string const& func() const& // notice &
{
    return m.find("key")->second;
}
std::string func() && // notice &&
{
    return std::move(m.find("key")->second);
}
```

do rvalue overloads and return moved-into values by value when consuming temporaries instead of returning references into
them.

Then the

```cpp
auto&& __range=exp;
```

line does reference lifetime extension on the by-value returned string, and no more dangling references.

As a general rule, never return a range by reference to a parameter that could be an rvalue.

