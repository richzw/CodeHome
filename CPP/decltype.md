### Question

As I understood in C++11 `decltype(expression)` is used to deduce the exact same type of the given expression. 
But when the expression is put into parentheses itself, then the deduces type is `lvalue reference` to the expression type. 
For example:

```cpp
int x;
decltype(x) y = x;
```

is equivalent to `int y = x;` but,

```cpp
int x;
decltype((x)) y = x;
```

is equivalent to `int& y = x;`.

Respectively

```cpp
 decltype(auto) f1()
 {
   int x = 0;
   return x; // decltype(x) is int, so f1 returns int
 }
```

but

```cpp
 decltype(auto) f2()
 {
   int x = 0;
   return (x); // decltype((x)) is int&, so f2 returns int&
 }
```

What is the rationale for this behavior to be chose by the standard committee?

### Answer

They wanted a way to get the type of declaration of an identifier.

They also wanted a way to get the type of an expression, including information about if it is a temporary or not.

`decltype(x)` gives the declared type of the identifier `x`. If you pass `decltype` something that is not an identifier, 
it determines the type, then appends `&` for `lvalues`, `&&` for `xvalues`, and nothing for `prvalues`.

Conceptually you can think of it as the difference between the type of a variable and the type of an expression. 
But that is not quite how the standard describes it.

They could have used two different keywords to mean these two things. They did not.

