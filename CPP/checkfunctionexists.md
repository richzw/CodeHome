Q:

Is it possible to write a C++ template to check for a function's existence?

---------------------------------------

```cpp
#include <iostream>

struct Hello
{
    int helloworld()
    { return 0; }
};

struct Generic {};


// SFINAE test
template <typename T>
class has_helloworld
{
    typedef char one;
    typedef long two;

    template <typename C> static one test( typeof(&C::helloworld) ) ;
    template <typename C> static two test(...);


public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};


int
main(int argc, char *argv[])
{
    std::cout << has_helloworld<Hello>::value << std::endl;
    std::cout << has_helloworld<Generic>::value << std::endl;
    return 0;
}
```

check `operator ==` exists?

```cpp
namespace CHECK  // namespace to let "operator ==" not become global
{
  typedef char no[7];
  template<typename T> no& operator == (const T&, const T&);

  template <typename T>
  struct opEqualExists // *(T*)(0) can be replaced by *new T[1] also
  {
    enum { value = (sizeof(*(T*)(0) == *(T*)(0)) != sizeof(no)) };
  };
}

//Usage:

std::cout<<CHECK::opEqualExists<A>::value<<std::endl;
```

