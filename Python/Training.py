#Function and Scope
a_string = "This is a global variable"
def foo():
    print locals()
print globals()
foo()

#variable resolution rules
a_string = "This is a global variable"
def foo():
    a_string = "test"
    print locals()
foo()

#Function arguments and parameters
def foo(x, y=0):
    return x - y
foo(3, 1)
foo(3)
foo(y=1, x=3)

#Nested functions
def outer():
    x = 1
    def inner():
        print x
    inner()

#Function are first class object
def foo():
    pass
foo.__class__
issubclass(foo.__class__, object)

def add(x, y):
    return x+y
def sub(x, y):
    return x-y
def myapply(func, x, y)
    return func(x, y)
myapply(add, 2, 1)
myapply(sub, 2, 1)

#Closure
def outer():
    x = 1
    def inner():
        print x
    return inner



#class method
class Human(object):
    weight = 12
    @classmethod
    def get_weight(self):
        return self.weight

#instance method
class Human1(object):
    def __init__(self, weight):
        self.weight = weight

    def get_weight(self):
        return self.weight

#static method
class Human2(object):
    @staticmethod
    def add(a, b):
        return a+b
    def get_weight(self):
        return self.add(1, 2)


#args and **kwargs
def one(*args):
    print args
one()
one(1, 2, 3)

def two(x, y, *args):
    print x, y, args
two('a', 'b', 'c')

def add(x, y):
    return x+y
lst = [1, 2]
add(lst[0], lst[1])
add(*lst)
dct = {'x':1, 'y':2}
bar(**dct)

def myfoo(**kwargs):
    print kwargs
myfoo()
myfoo(x=1, y=2)

#Decorator
def hello(fn):
    print "hello %s" % fn.__name__[::-1].upper()
@hello
def baby():
    pass
'''
def hello(fn):
    def wrapper():
        print "hello, %s" % fn.__name__
        fn()
        print "goodby, %s" % fn.__name__
    return wrapper
 
@hello
def foo():
    print "i am foo"
 
foo()
'''

'''*args, **kwds'''
def logger(func):
    def inner(*args, **kwargs):
        print "Arguments were: %s, %s" % (args, kwargs)
        return func(*args, **kwargs)
    return inner
@logger
def foo1(x, y=1):
    return x*y

def makeHtmlTag(tag, *args, **kwds):
    def real_decorator(fn):
        css_class = " class='{0}'".format(kwds["css_class"]) \
                                     if "css_class" in kwds else ""
        #return "<"+tag+css_class+">" + fn() + "</"+tag+">"
        def wrapped():
            return "<"+tag+css_class+">" + fn() + "</"+tag+">"
        return wrapped
    return real_decorator
 
#@makeHtmlTag(tag="b", css_class="bold_css")
@makeHtmlTag(tag="i", css_class="italic_css")
def hello():
    return "hello world"
 
print hello()


if __name__ == '__main__':
    pass
