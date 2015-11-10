

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


