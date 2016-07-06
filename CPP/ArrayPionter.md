### Question

Today I read a C snippet which really confuses me:

```c
#include <stdio.h>

int
main(void)
{
    int a[] = {0, 1, 2, 3};

    printf("%d\n", *(*(&a + 1) - 1));
    return 0;
}
```

In my opinion, `&a + 1` makes no sense, but it runs without error. Could someone please explain what it means?

### Answer

First a little reminder (or something new if you didn't know this before): For any array or pointer p and index i the expression p[i] is exactly the same as *(p + i).

Now to hopefully help you understand what's going on...

The array a in your program is stored somewhere in memory, exactly where doesn't really matter. To get the location of where a is stored, i.e. get a pointer to a, you use the address-of operator & like &a. The important thing to learn here is that a pointer by itself doesn't mean anything special, the important thing is the base type of the pointer. The type of a is int[4], i.e. a is an array of four int elements. The type of the expression &a is a pointer to an array of four int, or int (*)[4]. The parentheses are important, because the type int *[4] is an array of four pointers to int, which is quite a different thing.

Now to get back to the initial point, that p[i] is the same as *(p + i). Instead of p we have &a, so our expression *(&a + 1) is the same as (&a)[1].

Now that explains what *(&a + 1) means and what it does. Now let us think for a while about the memory layout of the array a. In memory it looks something like

```
+---+---+---+---+
| 0 | 1 | 2 | 3 |
+---+---+---+---+
^
|
&a
```

The expression (&a)[1] treats &a as it was an array of arrays, which it definitely isn't, and accessing the second element in this array, which will be out of bounds. This of course technically is undefined behavior. Let us run with it for a moment though, and consider how that would look like in memory:

```
+---+---+---+---+---+---+---+---+
| 0 | 1 | 2 | 3 | . | . | . | . |
+---+---+---+---+---+---+---+---+
^               ^
|               |
(&a)[0]         (&a)[1]
```

Now remember that the type of a (which is the same as (&a)[0] and therefore means that (&a)[1] must also be this type) is array of four int. Since arrays naturally decays to pointers to its first element, the expression (&a)[1] is the same as &(&a)[1][0], and its type is pointer to int. So when we use (&a)[1] in an expression what the compiler gives us is a pointer to the first element in the second (non-existing) array of &a. And once again we come to the p[i] equals *(p + i) equation: (&a)[1] is a pointer to int, it's p in the *(p + i) expression, so the full expression is *((&a)[1] - 1), and looking at the memory layout above subtracting one int from the pointer given by (&a)[1] gives us the element before (&a)[1] which is the last element in (&a)[0], i.e. it gives us (&a)[0][3] which is the same as a[3].

So the expression *(*(&a + 1) - 1) is the same as a[3].

