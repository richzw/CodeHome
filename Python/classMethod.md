@staticmethod function is nothing more than a function defined inside a class. It is callable without instantiating the class first. It’s definition is immutable via inheritance.

@classmethod function also callable without instantiating the class, but its definition follows Sub class, not Parent class, via inheritance, can be overridden by subclass. That’s because the first argument for @classmethod function must always be cls (class).

```python
class A(object):
    def foo(self,x):
        print "executing foo(%s,%s)"%(self,x)

    @classmethod
    def class_foo(cls,x):
        print "executing class_foo(%s,%s)"%(cls,x)

    @staticmethod
    def static_foo(x):
        print "executing static_foo(%s)"%x    

a=A()
```

----------------------------------------------------------------------------
With classmethods, the class of the object instance is implicitly passed as the first argument instead of self.

```python
a.class_foo(1)
 executing class_foo(<class '__main__.A'>,1)
```

You can also call class_foo using the class. In fact, if you define something to be a classmethod, it is probably because you intend to call it from the class rather than from a class instance. A.foo(1) would have raised a TypeError, but A.class_foo(1) works just fine:

```python
A.class_foo(1)
 executing class_foo(<class '__main__.A'>,1)
```
One use people have found for class methods is to create inheritable alternative constructors.
-----------------------------------------------------------------------------------------------------------------------------
With staticmethods, neither self (the object instance) nor cls (the class) is implicitly passed as the first argument. They behave like plain functions except that you can call them from an instance or the class:

```python
a.static_foo(1)
executing static_foo(1)

A.static_foo('hi')
 executing static_foo(hi)
```

Staticmethods are used to group functions which have some logical connection with a class to the clas
