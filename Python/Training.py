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


#class decorator
class myDecorator(object):
    def __init__(self, fn):
        print "inside myDecorator.__init__()"
        self.fn = fn
    def __call__(self):
        self.fn()
        print "inside myDecorator.__call__()"
@myDecorator
def aFunction():
    print "inside aFunction()"

print "Finished decorating aFunction()"

aFunction()

class makeHtmlTag(object):
    def __init__(self, tag, css_class=""):
        self._tag = tag
        self._css_class = " class = '{0}'".format(css_class)\
                          if css_class != "" else ""
    def __call__(self, fn):
        def wrapped(*args, **kwargs):
            return "<" + self._tag +self._css_class +">"\
                   + fn(*args, **kwargs) + "</" + self._tag + ">"
        return wrapped
    
@makeHtmlTagClass(tag="b", css_class="bold_css")
@makeHtmlTagClass(tag="i", css_class="italic_css")
def hello(name):
    return "Hello, {}".format(name)
 
print hello("Benz")

#set arguments of decorator
# method 1
def decorate_A(func):
    def wrap_function(*args, **kwargs):
        kwargs['str'] = 'Hello!'
        return func(*args, **kwargs)
    return wrap_function
@decorate_A
def print_msg_A(*args, **kwargs):
    print(kwargs['str'])
print_msg_A()

#method 2
def decorate_B(func):
    def wrap_function(*args, **kwargs):
        str = 'Hello!'
        return func(str, *args, **kwargs)
    return wrap_function
@decorate_B
def print_msg_B(str, *args, **kwargs):
    print(str)
print_msg_B()

#method 3
def decorate_C(func):
    def wrap_function(*args, **kwargs):
        str = 'Hello'
        args = args + (str,)
        return func(*args, **kwargs)
    return wrap_function

class Printer:
    @decorate_C
    def print_msg(self, str, *args, **kwargs):
        print(str)
p = Printer()
p.print_msg()

#side effect of decorator, eliminate it
from functools import wraps
def hello(fn):
    @wraps(fn)
    def wrapper():
        print "hello, %s" % fn.__name__
        fn()
        print "bye, %s" % fn.__name__
    return wrapper
@hello
def foo():
    print 'i am foo'
    pass
foo()
print foo.__name__
print foo.__doc__

#examples
# ex 1
from functools import wraps
def memo(fn):
    cache = {}
    miss = object()

    @wraps(fn)
    def wraps(*args):
        result = cache.get(args, miss)
        if result is miss:
            result = fn(*args)
            cache[args] = result
        return result
    return wrapper
@memo
def fib(n):
    if n < 2:
        return n
    return fib(n-1) + fib(n-2)

#ex 2
class MyApp():
    def __init__(self):
        self.func_map = {}
    def register(self, name):
        def func_wrapper(func):
            self.func_map[name] = func
            return func
        return func_wrapper
    def call_method(self, name=None):
        func = self.func_map.get(name, None)
        if func is None:
            raise Exception("No function registered against - " + str(name))
        return func()

app = MyApp()
@app.register('/')
def main_page_func():
    return "This is the main page"
@app.register('/next_page')
def next_page_func():
    return "This is the next page"

print app.call_method('/')
print app.call_method('/next_page')

#ex 3
import inspect
def advance_logger(logLevel):
   def get_line_number():
       return inspect.currentframe().f_back.f_back.f_lineno
    def _basic_log(fn, result, *args, **kwargs):
        print "function  =  " + fn.__name__
        print "     arguments = {0} {1}".format(args, kwargs)
        print "     return    = {0}".format(result)
    def info_log_decorate(fn):
        @wraps(fn)
        def wrapper(*args, **kwargs):
            result = fn(*args, **kwargs)
            _basic_log(fn, result, args, kwargs)
        return wrapper
    def debug_log_decorate(fn):
        @wraps(fn)
        def wrapper(*args, **kwargs):
            ts = time.time()
            result = fn(*args, **kwargs)
            te = time.time()
            _basic_log(fn, result, args, kwargs)
            print "    time   =  %.6f sec" % (te - ts)
            print "    called_from_line : " + str(get_line_number())
        return wrapper
    if logLevel is "debug":
        return debug_log_decorate
    else:
        return info_log_decorate

@advance_logger
def sum_num(n):
    s = 0
    for i in xrange(n+1):
        s += i
    return s

print sum_num(100)
print sum_num(1000000)


# here is more example...
#https://wiki.python.org/moin/PythonDecoratorLibrary 

if __name__ == '__main__':
    pass
