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


