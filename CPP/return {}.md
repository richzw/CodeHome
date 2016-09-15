### Question

What does the statement

```cpp
return {};
```

in C++11 indicate, and when to use it instead of (say)

```cpp
return NULL;
```

or

```cpp
return nullptr;
```

### Answer

This is probably confusing:

```cpp
int foo()
{
  return {};   // honestly, just return 0 - it's clearer
}
```

This is probably not:

```cpp
SomeObjectWithADefaultConstructor foo()
{
  return {};
  // equivalent to return SomeObjectWithADefaultConstructor {};
}
```

`return {};` means that `{}` is the initializer for the return value. The return value is list-initialized with an empty list.

Here is some background on the return value, based on `[stmt.return]` in the C++ Standard:

> For a function that returns by value (i.e. the return type is not a reference and not void), there is a temporary object called the return value. This object is created by the return statement, and its initializers depend on what was in the return statement.

> The return value survives until the end of the full-expression in the code that called the function; if it has class type, then its destructor will run unless it has lifetime extended by the caller binding a reference directly to it.

> The return value can be initialized in two different ways:

  - return some_expression; - the return value is copy-initialized from some_expression
  - return { possibly_empty_list }; - the return value is list-initialized from the list.
  
Assuming T is the function's return type, then note that `return T{};` is different to `return {}:` in the former, a temporary `T{}` is 
created, and then the return value is copy-initialized from that temporary.

This will fail to compile if T has no accessible copy/move-constructor, but `return {};` will succeed even if those constructors are not
present. Accordingly, `return T{};` may show side-effects of the copy-constructor etc., although this is a copy elision context so it may 
not.



