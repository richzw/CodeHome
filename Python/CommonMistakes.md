[Source](http://www.toptal.com/python/top-10-mistakes-that-python-programmers-make)

---------------------------

- **Misusing expressions as defaults for function arguments**

```python
>>> def foo(bar=[]):        # bar is optional and defaults to [] if not specified
...    bar.append("baz")    # but this line could be problematic, as we'll see...
...    return bar

>>> foo()
["baz"]
>>> foo()
["baz", "baz"]
>>> foo()
["baz", "baz", "baz"]
```

The more advanced Python programming answer is that _the default value for a function argument is only evaluated once, at the time that the function is defined._ 

One common workaround

```python
>>> def foo(bar=None):
...    if bar is None:		# or if not bar:
...        bar = []
...    bar.append("baz")
...    return bar
```

------------------------------------

- **Using class variables incorrectly**

```python
>>> class A(object):
...     x = 1
...
>>> class B(A):
...     pass
...
>>> class C(A):
...     pass
...
>>> print A.x, B.x, C.x
1 1 1

>>> B.x = 2
>>> print A.x, B.x, C.x
1 2 1

>>> A.x = 3
>>> print A.x, B.x, C.x
3 2 3
```

So in the above code, since the attribute `x` is not found in class `C`, it will be looked up in its base classes (only `A` in the above example, although Python supports multiple inheritance). In other words, `C` doesn’t have its own `x` property, independent of `A`. Thus, references to `C.x` are in fact references to `A.x`.

-------------------------------

- **Specifying parameters incorrectly for an exception block**

```python
>>> try:
...     l = ["a", "b"]
...     int(l[2])
... except ValueError, IndexError:  # To catch both exceptions, right?
...     pass
...
Traceback (most recent call last):
  File "<stdin>", line 3, in <module>
IndexError: list index out of range
```
 
in the above code, the `IndexError` exception is _not_ being caught by the `except` statement; rather, the exception instead ends up being bound to a parameter named `IndexError`. 

Workaround:

```python
>>> try:
...     l = ["a", "b"]
...     int(l[2])
... except (ValueError, IndexError) as e:  
...     pass
...
>>>
```


