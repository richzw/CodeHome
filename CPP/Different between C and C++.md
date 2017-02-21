Withe following codes

```c
int x = 100;

while ( 0 <-------------------- x )
{
    printf("%d ", x);
}
```

In C, --x is a value, not an lvalue. Its effect is to decrement x, and evaluate to the newly assigned value of x. 
Since --x is not an lvalue, it cannot be decremented.

In C++, --x is an lvalue, not an rvalue. Its effect is to decrement x, and evaluate to x as an lvalue. Since --x is an lvalue
again, it can be decremented again.

The reason why it makes sense for --x to be an lvalue in C++ is because C++ introduced reference types. Given

```c
void f(int &);
int i;
```

it may make sense to call f(--i), which passes i by reference after decrementing it.

Since C doesn't have reference types, there's little point in --i being an lvalue. Historically, it never was, and unlike C++, 
C never gained a compelling reason to change the rules.

Note that C++ required more extensive changes than making --x an lvalue to actually let it work. Making --x an lvalue, without
anything else, would make --x undefined behaviour, because there would not be a sequence point between the modification to x 
and the subsequent lvalue-to-value conversion. Even more clearly so for ----x. C++ had to modify the sequencing rules to make
it work. In C, modifications to the sequencing rules might cause problems for existing compilers to conform to the new rules, 
so such modifications would likely be rejected unless there's a big benefit.

