### Question

I have the following problem:

```cpp
template< size_t... N_i >
class A
{
  public:

    // ...

    void foo()
    {
      bar( /* 0,...,0 <- sizeof...(N_i) times */);
    }
};
```

I want to call a function bar and pass `sizeof...(N_i)` many arguments to it which are all `zeros`, e.g., `bar(0,0,0)` in case
`sizeof...(N_i) == 3`. How can this can be implemented?

### Answer

`bar(((void)N_i, 0)...);`

The comma operator will discard `N_i`, yielding just the right-hand operand's value `(0)`. The cast is to prevent a warning 
about `N_i` being discarded.
