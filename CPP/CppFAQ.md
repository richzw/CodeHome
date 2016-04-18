
[CPPFAQ](https://isocpp.org/wiki/faq)

-------------------------------------

**Question: Why can't C functions be name-mangled?**

Answer:

First, C came first. As such, what C does is, sort of, the "default". It does not mangle names because it just doesn't. A function name is a function name. A global is a global, and so on.

Then C++ came along. C++ wanted to be able to use the same linker as C, and to be able to link with code written in C. But C++ could not leave the C **"mangling"** (or, lack there of) as is. Check out the following example:

```c
int function(int a);
int function();
```

In C++, these are distinct functions, with distinct bodies. If none of them are mangled, both will be called "function" (or "_function"), and the linker will complain about the redefinition of a symbol. C++ solution was to mangle the argument types into the function name. So, one is called `_function_int` and the other is called `_function_void` (not actual mangling scheme) and the collision is avoided.

Now we're left with a problem. If `int function(int a)` was defined in a C module, and we're merely taking its header (i.e. declaration) in C++ code and using it, the compiler will generate an instruction to the linker to import `_function_int`. When the function was defined, in the C module, it was not called that. It was called `_function`. This will cause a linker error.

To avoid that error, during the declaration of the function, we tell the compiler it is a function designed to be linked with, or compiled by, a C compiler:

```c
extern "C" int function(int a);
```

The C++ compiler now knows to import `_function` rather than `_function_int`, and all is well.

Extra:

If you want to call a function in a C library called `foo(int x, const char *y`), it's no good letting your C++ compiler mangle that into `foo_I_cCP()` (or whatever, just made up a mangling scheme on the spot here) just because it can.

That name won't resolve, the function is in C and its name does not depend on its list of argument types. So the C++ compiler has to know this, and mark that function as being C to avoid doing the mangling.

Remember that said C function might be in a library whose source code you don't have, all you have is the pre-compiled binary and the header. So your C++ compiler can't do "it's own thing", it can't change what's in the library after all.

