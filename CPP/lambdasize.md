### Question:

What the size of lambda in C++?

```cpp
#include <iostream>
#include <string>

int main()
{
  auto f = [](){ return 17; };
  std::cout << f() << std::endl;
  std::cout << &f << std::endl;
  std::cout << sizeof(f) << std::endl;
}
```

Output:

```
17
0x7d90ba8f626f
1
```

### Answer

The lambda in question actually has no state.

Examine:

```cpp
struct lambda {
  auto operator()() const { return 17; }
};
```

And if we had `lambda f;`, it is an empty class. Not only is the above `lambda` functionally similar to your lambda, it is (basically) 
how your lambda is implemented! (It also needs an implicit cast to function pointer operator, and the name lambda is going to be replaced 
with some compiler-generated pseudo-guid)


### Source

[1](http://stackoverflow.com/questions/37481767/why-is-the-size-of-a-lambda-1-in-c)


