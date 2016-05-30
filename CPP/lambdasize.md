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

The lambda in question actually has no state. A lambda is not a function pointer. A lambda is an instance of a class.

Examine:

```cpp
struct lambda {
  auto operator()() const { return 17; }
};
```

And if we had `lambda f;`, it is an empty class. Not only is the above `lambda` functionally similar to your lambda, it is (basically) how your lambda is implemented! (It also needs an implicit cast to function pointer operator, and the name lambda is going to be replaced with some compiler-generated pseudo-guid)

In C++, objects are not pointers. They are actual things. They only use up the space required to store the data in them. A pointer to an object can be larger than an object.

While you might think of that lambda as a pointer to a function, it isn't. You **cannot** reassign the `auto f = [](){ return 17; };` to a different function or lambda!

```cpp
 auto f = [](){ return 17; };
 f = [](){ return -42; };
```

the above is _illegal_. There is no room in `f` to store which function is going to be called -- that information is stored in the _type_ of `f`, **not** in the _value_ of `f`!

If you did this:

```cpp
int(*f)() = [](){ return 17; };
```

or this:

```cpp
std::function<int()> f = [](){ return 17; };
```

you are no longer storing the lambda directly. In both of these cases, `f = [](){ return -42; }` is _legal_ -- so in these cases, we are storing which function we are invoking in the value of `f`. And `sizeof(f)` is no longer `1`, but rather `sizeof(int(*)())` or larger (basically, be pointer sized or larger, as you expect. `std::function` have a min size implied by the standard (they have to be able to store "inside themselves" callables up to a certain size) which is at least as large as a function pointer in practice).

In the first case, you are storing a function pointer to a function that behaves as-if you called that lambda. This only works for stateless lambdas (ones with an empty `[]` capture list).

In the second case, you are creating a type-erasure class `std::function<int()>` instance that (in this case) uses `placement new` to store a copy of the `size-1` lambda in an internal buffer (and, if a larger lambda was passed in (with more state), would use heap allocation).

Now that you understand that your `f` is in fact stateless, there should be another question in your head: _why not size 0?_

-----------------------------------------------------------

All objects in C++ must have a minimium size of `1` under the standard, and two objects of the same type cannot have the same address. These are connected, because an array of type `T` will have the elements placed `sizeof(T)` apart.

As a lambda is equivalent to a class with `operator()` overloaded, stateless lambdas (with a `[]` capture list) are all empty classes. They have `sizeof` of `1`. In fact, if you inherit from them (which is allowed!), they will take up no space _so long as it doesn't cause a same-type address collision_. (This is known as the empty base optimization).

```cpp
template<class T>
struct toy:T {
  toy(toy const&)=default;
  toy(toy &&)=default;
  toy(T const&t):T(t) {}
  toy(T &&t):T(std::move(t)) {}
  int state = 0;
};

template<class Lambda>
toy<Lambda> make_toy( Lambda const& l ) { return {l}; }
```

the `sizeof(make_toy( []{std::cout << "hello world!\n"; } ))` is `sizeof(int)` (well, the above is illegal because you cannot create a lambda in a non-evaluated context: you have to create a named `auto toy = make_toy(blah);` then do `sizeof(blah)`, but that is just noise).  `sizeof([]{std::cout << "hello world!\n"; })` is still `1` (similar qualifications).

If we create another toy type:

```cpp
template<class T>
struct toy2:T {
  toy2(toy2 const&)=default;
  toy2(T const&t):T(t), t2(t) {}
  T t2;
};
template<class Lambda>
toy2<Lambda> make_toy2( Lambda const& l ) { return {l}; }
```

this has **two** copies of the lambda. As they cannot share the same address, `sizeof(toy2(some_lambda))` is `2`


### Source

[1](http://stackoverflow.com/questions/37481767/why-is-the-size-of-a-lambda-1-in-c)


