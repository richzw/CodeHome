
[Source](http://www.toptal.com/python/python-class-attributes-an-overly-thorough-guide)

--------------------

![Pic](http://assets.toptal.io/uploads/blog/image/301/toptal-blog-image-1392824596580.png)


------------------------

**Handling assignment**

- If a class attribute is set by accessing the class, it will override the value for _all instances_. For example:

```python
foo = MyClass(2)
foo.class_var
## 1
MyClass.class_var = 2
foo.class_var
## 2
```

- If a class variable is set by accessing an instance, it will override the value _only_ for that instance. 
This essentially overrides the class variable and turns it into an instance variable available, intuitively, only for that instance.

```python
foo = MyClass(2)
foo.class_var
## 1
foo.class_var = 2
foo.class_var
## 2
MyClass.class_var
## 1
```

**Quiz question:** What if your class attribute has a mutable type? You can manipulate (mutilate?) the class attribute
by accessing it through a particular instance and, in turn, end up manipulating the referenced object that all instances are accessing 

--------------------------

**So when would you use them?**

- _Storing constants._

