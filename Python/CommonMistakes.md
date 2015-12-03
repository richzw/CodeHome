
- ****

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



