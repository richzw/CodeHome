
### Question

We can pass reference of an array to a function like:

```c
void f(int (&a)[5]);

int x[5];
f(x);     //okay
int y[6];
f(y);     //error - type of y is not `int (&)[5]`.
```

Or even better, we can write a function template:

```c
template<size_t N>
void f(int (&a)[N]); //N is size of the array!

int x[5];
f(x);     //okay - N becomes 5
int y[6];
f(y);     //okay - N becomes 6
```

Now my question is, how to return reference of an array from a function? I want to return array of folllowing types from a function:

```
int a[N];
int a[M][N];
int (*a)[N];
int (*a)[M][N];
```

where `M` and `N` is known at compile time!

----------------------------------------------------

### Answer

If you want to return a reference to an array from a function, the declaration would look like this:

```c
// an array
int global[10];

// function returning a reference to an array
int (&f())[10] {
   return global;
}
```

The declaration of a function returning a reference to an array looks the same as the declaration of a variable that is a reference to 
an array - only that the function name is followed by `()`, which may contain parameter declarations:

```c
int (&variable)[1][2];
int (&functionA())[1][2];
int (&functionB(int param))[1][2];
Such declarations can be made much clearer by using a typedef:

typedef int array_t[10];

array_t& f() {
   return global;
}
```

If you want it to get really confusing, you can declare a function that takes a reference to an array and also returns such a reference:

```c
template<int N, int M>
int (&f(int (&param)[M][N]))[M][N] {
   return param;
}
```

Pointers to arrays work the same, only that they use `*` instead of `&`


With C++11's trailing return type syntax, you can also write:

```cpp
auto foo () -> int (&)[3]
{
    return some_array;
}
```


### Source

[1](http://stackoverflow.com/questions/5398930/general-rules-of-passing-returning-reference-of-array-not-pointer-to-from-a-fu/5399014#5399014)

