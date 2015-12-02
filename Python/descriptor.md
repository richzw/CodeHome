[Source](http://nbviewer.ipython.org/urls/gist.github.com/ChrisBeaumont/5758381/raw/descriptor_writeup.ipynb)


The punchline: **descriptors are reusable properties**

------------------------

fundamentally, `descriptors` are properties that you can reuse. That is, `descriptors` let you write code that looks like this

```python
f = Foo()
b = f.bar
f.bar = c
del f.bar
```

and, behind the scenes, calls custom methods when trying to access (`b = f.bar`), assign to (`f.bar = c`), 
or delete an instance variable (`del f.bar`)

**Properties disguise function calls as attributes**

--------------------------

```python
class Movie(object):
    def __init__(self, title, rating, runtime, budget, gross):
        self._budget = None

        self.title = title
        self.rating = rating
        self.runtime = runtime
        self.gross = gross
        self.budget = budget
        
    @property
    def budget(self):
        return self._budget
    
    @budget.setter
    def budget(self, value):
        if value < 0:
            raise ValueError("Negative value not allowed: %s" % value)
        self._budget = value
        
    def profit(self):
        return self.gross - self.budget

    
m = Movie('Casablanca', 97, 102, 964000, 1300000)
print m.budget       # calls m.budget(), returns result
try:
    m.budget = -100  # calls budget.setter(-100), and raises ValueError
except ValueError:
    print "Woops. Not allowed"
```

We specify a getter method with a `@property` decorator, and a setter method with a `@budget.setter` decorator. When we do that, 
Python automatically calls the getter whenever anybody tries to access the budget. 
Likewise Python automatically calls `budget.setter` whenever it encounters code like `m.budget = value`.

**Properties Get Tedious**

If the member of `Movie` should check its value, the `descriptor` will make the code so tedious. Here is one solution

```python
from weakref import WeakKeyDictionary

class NonNegative(object):
    """A descriptor that forbids negative values"""
    def __init__(self, default):
        self.default = default
        self.data = WeakKeyDictionary()
        
    def __get__(self, instance, owner):
        # we get here when someone calls x.d, and d is a NonNegative instance
        # instance = x
        # owner = type(x)
        return self.data.get(instance, self.default)
    
    def __set__(self, instance, value):
        # we get here when someone calls x.d = val, and d is a NonNegative instance
        # instance = x
        # value = val
        if value < 0:
            raise ValueError("Negative value not allowed: %s" % value)
        self.data[instance] = value

        
class Movie(object):
    
    #always put descriptors at the class-level
    rating = NonNegative(0)
    runtime = NonNegative(0)
    budget = NonNegative(0)
    gross = NonNegative(0)
    
    def __init__(self, title, rating, runtime, budget, gross):
        self.title = title
        self.rating = rating
        self.runtime = runtime
        self.budget = budget
        self.gross = gross
    
    def profit(self):
        return self.gross - self.budget
    
    
m = Movie('Casablanca', 97, 102, 964000, 1300000)
print m.budget  # calls Movie.budget.__get__(m, Movie)
m.rating = 100  # calls Movie.budget.__set__(m, 100)
try:
    m.rating = -1   # calls Movie.budget.__set__(m, -100)
except ValueError:
    print "Woops, negative value"
```

-----------------------------------

**Recipes and Gotchas**

- **Put descriptors at the class level**

```python
class Broken(object):
    y = NonNegative(5)
    def __init__(self):
        self.x = NonNegative(0)  # NOT a good descriptor
        
b = Broken()
print "X is %s, Y is %s" % (b.x, b.y)
```

- **Make sure to keep instance-level data instance-specific**

```python
class BrokenNonNegative(object):
    def __init__(self, default):
        self.value = default
        
    def __get__(self, instance, owner):
        return self.value
    
    def __set__(self, instance, value):
        if value < 0:
            raise ValueError("Negative value not allowed: %s" % value)
        self.value = value
        
class Foo(object):
    bar = BrokenNonNegative(5) 
    
f = Foo()
try:
    f.bar = -1
except ValueError:
    print "Caught the invalid assignment"
```

That seems to work fine. The problem here is that all instances of Foo share the same bar instance, leading to this flavor of sadness:

- **Beware unhashable descriptor owners**

`NonNegative` uses a dictionary to keep instance-specific data separate. This normally works fine, unless you want to use descriptors with unhashable objects:

```python
class MoProblems(list):  #you can't use lists as dictionary keys
    x = NonNegative(5)
        
m = MoProblems()
print m.x  # womp womp
```

Because instances of `MoProblems` (which is a subclass of list) aren't hashable, they can't be used as keys in the data dictionary for `MoProblems.x`. There are a few ways around this, though none are perfect. The best approach is probably to "label" your descriptors

```python
class Descriptor(object):
    
    def __init__(self, label):
        self.label = label
        
    def __get__(self, instance, owner):
        print '__get__', instance, owner
        return instance.__dict__.get(self.label)
    
    def __set__(self, instance, value):
        print '__set__'
        instance.__dict__[self.label] = value
        

class Foo(list):
    x = Descriptor('x')
    y = Descriptor('y')
    
f = Foo()
f.x = 5
print f.x
```

However,

```python
class Foo(object):
    x = Descriptor('y')
    
f = Foo()
f.x = 5
print f.x

f.y = 4    #oh no!
print f.x
```

- **Labeled Descriptors with Metaclasses**

Because descriptor labels match the variable name they are assigned to, some people use metaclasses to take care of this bookkeeping automatically:

```python
class Descriptor(object):
    def __init__(self):
        #notice we aren't setting the label here
        self.label = None
        
    def __get__(self, instance, owner):
        print '__get__. Label = %s' % self.label
        return instance.__dict__.get(self.label, None)
    
    def __set__(self, instance, value):
        print '__set__'
        instance.__dict__[self.label] = value

        
class DescriptorOwner(type):
    def __new__(cls, name, bases, attrs):
        # find all descriptors, auto-set their labels
        for n, v in attrs.items():
            if isinstance(v, Descriptor):
                v.label = n
        return super(DescriptorOwner, cls).__new__(cls, name, bases, attrs)

        
class Foo(object):
    __metaclass__ = DescriptorOwner
    x = Descriptor()
    
f = Foo()
f.x = 10
print f.x
```

