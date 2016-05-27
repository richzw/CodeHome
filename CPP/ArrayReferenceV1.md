I'll propose few solutions which are in my opinion more readable than the extremely direct answer to this question. I'm sure there are C grammar enthusiasts out there and I apologize to them for I have terrible memory and I'm not able to remember those C rules.

**Type alias**

You can avoid the weird C-based grammar by using a type alias:

```c
struct A {
    using data_type = int[10];
    data_type data;
    data_type& f1() { return data; }
    data_type const& f2() const { return data; }
};
```

or with typedef (for before C++11):

```c
struct A {
    typedef int data_type[10];
    data_type data;
    data_type& f1() { return data; }
    data_type const& f2() const { return data; }
};
```

**Auto**

Since C++14 you can also use auto return types:

```c
struct A {
    int data[10];
    auto& f1() { return data; }
    auto const& f2() const { return data; }
};
```

**Standard array**

As of C++11 you can also just use std::array:

```c
struct A {
    using data_type = std::array<int, 10>;
    data_type data;
    data_type& f1() { return data; }
    data_type const& f2() const { return data; }
};
```

and simplify it to:

```c
struct A {
    std::array<int, 10> data;
};
```

which is somewhat functionally equivalent but easier on the eyes.

