
**Iteration vs Iterator vs Iterable**

--------------------

**Iterable**
An iterable is any object in Python which has an `__iter__` or a `__getitem__` method defined which returns an iterator or 
can take indexes (Both of these dunder methods are fully explained in a previous chapter). 
In short an iterable is any object which can provide us with an iterator. So what is an iterator?

**Iterator**

An iterator is any object in Python which has a `next` (Python2) or `__next__` method defined. That’s it. That’s an iterator. 
Now let’s understand iteration.

**Iteration**
In simple words it is the process of taking an item from something e.g a list. 
When we use a loop to loop over something it is called iteration. It is the name given to the process itself. 
Now as we have a basic understanding of these terms let’s understand generators.

```python
>>> s = 'cat'      # s is an ITERABLE
                   # s is a str object that is immutable
                   # s has no state
                   # s has a __getitem__() method 

>>> t = iter(s)    # t is an ITERATOR
                   # t has state (it starts by pointing at the "c"
                   # t has a next() method and an __iter__() method

>>> next(t)        # the next() function returns the next value and advances the state
'c'
>>> next(t)        # the next() function returns the next value and advances
'a'
>>> next(t)        # the next() function returns the next value and advances
't'
>>> next(t)        # next() raises StopIteration to signal that iteration is complete
Traceback (most recent call last):
...
StopIteration

>>> iter(t) is t   # the iterator is self-iterable
```

