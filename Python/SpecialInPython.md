

--------------------------

- **Python does not allow assignments in expressions**

Python wants to clearly separate statements and expressions, so

```python
line = f.readline()
while line:
    #do something with line
    line = f.readline()
```

rather than

```python
while line = f.readline():
    # do something here
```

However, it could be

```python
for line in iter(f.readline, ""):
    # do something with line
```

----------------------------------------------------------

- **Singleton Pattern in Python**

```python
def singleton(object, instantiated=[]):
    "Raise an exception if an object of this class has been instantiated before."
    assert object.__class__ not in instantiated, \
        "%s is a Singleton class but is already instantiated" % object.__class__
    instantiated.append(object.__class__)

class YourClass:
    "A singleton class to do something ..."
    def __init__(self, args):
        singleton(self)
        ...
```

------------------------------------------------------------

- **__init__ vs __new__**

Use `__new__` when you need to control the creation of a new instance. 

Use `__init__` when you need to control initialization of a new instance.

`__new__` is the first step of instance creation. It's called first, and is responsible for returning a new instance of your class. 

In contrast, `__init__` doesn't return anything; it's only responsible for initializing the instance after it's been created.

In general, you shouldn't need to override `__new__` unless you're subclassing an immutable type like str, int, unicode or tuple.

`__new__` is static class method, while `__init__` is instance method. ` __new__` has to create the instance first, so `__init__` can initialize it. Note that `__init__` takes self as parameter. Until you create instance there is no self.
