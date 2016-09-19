
### Question

How does a statement like (a = b) = c work in C++?

### Answer

The assignment expression `a = b` is not an `lvalue` in C, but it is in C++.

In the evolution of C++ from C, several expressions were made `"lvalue-aware"`, as it were, because lvalues are much more important in C++
than in C. In C, everything is trivial (trivially copyable and trivially destructible, all in the words of C++), so `lvalue-to-rvalue`
conversions (or `"lvalue conversions"`, as C calls them) aren't painful. In C++, copying and destruction are non-trivial concepts,
and by making expressions preserve `lvalue-ness`, a lot of copying and destructing can be avoided that was never necessary to begin with.

Another example is the conditional expression `(a ? b : c)`, which is not an `lvalue` in C, but can be a `lvalue` in C++.

```cpp
	int va, vb, vc;
	va = 1, vb = 2, vc = 3;

	(va = vb) = vc;
	std::cout << va << std::endl;
	std::cout << vb << std::endl;
	std::cout << vc << std::endl;

	std::cout << "==================" << std::endl;

	(va ? vb : vc) = 7;
	std::cout << va << std::endl;
	std::cout << vb << std::endl;
	std::cout << vc << std::endl;
```

Output

```
3
2
3
=================
3
7
3
```


