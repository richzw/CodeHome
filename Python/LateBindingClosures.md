
```python
>>> def create_multipliers():
...     return [lambda x : i * x for i in range(5)]
>>> for multiplier in create_multipliers():
...     print multiplier(2)
```

Output

```python
8
8
8
8
8
```

This happens due to Python’s _late binding behavior which says that the values of variables used in closures are looked up 
at the time the inner function is called_. So in the above code, 
whenever any of the returned functions are called, the value of i is looked up in the surrounding scope at the time it is called 

You can create a closure that binds immediately to its arguments by using a default arg like so:

```python
>>> def create_multipliers():
...     return [lambda x, i=i : i * x for i in range(5)]
...
>>> for multiplier in create_multipliers():
...     print multiplier(2)
...
0
2
4
6
8
```
