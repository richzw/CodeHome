
### Question

Consider this code:

```c++
struct A
{
    void foo() const
    {
        std::cout << "const" << std::endl;
    }

    private:

        void foo()
        {
            std::cout << "non - const" << std::endl;
        }
};

int main()
{
    A a;
    a.foo();
}
```

The compiler error is: `error: 'void A::foo()' is private`.

### Answer

When you call `a.foo();`, the compiler goes through overload resolution to find the best function to use. When it builds the overload set it finds

`void foo() const`

and

`void foo()`

Now, since a is not const, the non-const version is the best match, so the compiler picks void foo(). Then the access restrictions are 
put in place and you get a compiler error, since `void foo()` is private.

Remember, in overload resolution it is not `'find the best usable function'`. It is `'find the best function and try to use it'`. 
If it can't because of access restrictions or being deleted, then you get a compiler error.

In other words why does overload resolution comes before access control? Well, let's look at:

```c++
struct Base
{
    void foo() { std::cout << "Base\n"; }
};

struct Derived : Base
{
    void foo() { std::cout << "Derived\n"; }
};

struct Foo
{
    void foo(Base * b) { b->foo(); }
private:
    void foo(Derived * d) { d->foo(); }
};

int main()
{
    Derived d;
    Foo f;
    f.foo(&d);
}
```

Now let's say that I did not actually mean to make `void foo(Derived * d)` private. If access control came first then this program would
compile and run and Base would be printed. This could be very hard to track down in a large code base. Since access control comes after
overload resolution I get a nice compiler error telling me the function I want it to call cannot be called, and I can find the bug a lot easier.

