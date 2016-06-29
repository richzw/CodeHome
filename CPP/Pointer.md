### Question

The purpose of pointer is to save the address of specific variable. Then the memory structure of following code should look like

```c
int a = 5;
int *b = &a;
```

```
...... memory address ...... value
a ... 0x000002 ................... 5
b ... 0x000010 ................... 0x000002
```

Okay, fine. Then assume that now I want to save the address of pointer *b. Then we generally define double pointer `**c` as

```c
int a = 5;
int *b = &a;   
int **c = &b;
```

Then the memory structure looks like

```
...... memory address ...... value
a ... 0x000002 ................... 5
b ... 0x000010 ................... 0x000002
c ... 0x000020 ................... 0x000010
```

So `**c` refers the address of `*b`.

Now my question is, why

```c
int a = 5;
int *b = &a;   
int *c = &b;
```

### Answer

You need to go back to the fundamentals.

- variables have types
- variables hold values
- a pointer is a value
- a pointer refers to a variable
- if `p` is a pointer value then `*p` is a variable
- if `v` is a variable then `&v` is a pointer

```c
int a = 5;
int *b = &a;   
int *c = &b;
```

You get a warning because &b is of type int **, and you try to initialize a variable of type int *. There's no implicit conversions between those two types, leading to the warning.

To take the longer example you want to work, if we try to dereference f the compiler will give us an int, not a pointer that we can further dereference.

Also note that on 64-bit systems a pointer is typically 64 bits long while an int is usually only 32 bits long. If you dereference f and get an int, you lose half the value, and then you can't even cast it to a valid pointer.
