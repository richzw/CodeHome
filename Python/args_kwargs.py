#args and **kwargs
#ref http://stackoverflow.com/questions/3394835/args-and-kwargs
'''
*args = list of arguments -as positional arguments
**kwargs = dictionary - whose keys become separate keyword arguments and the values become values of these arguments.
'''
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

#You would use *args when you're not sure how many arguments might be passed to your function,
#i.e. it allows you pass an arbitrary number of arguments to your function
def print_everything(*args):
    for count, thing in enumerate(args):
        print '{0}.{1}'.format(count, thing)
print_everything('apple', 'banana', 'cabbage')

#**kwargs allows you to handle named arguments that you have not defined in advance
def table_things(**kwargs):
    for name, value in kwargs.items():
        print '{0}={1}'.format(name, value)
table_thing(apple='fruit', cabbage='vegetable')

def print_three_things(a, b, c):
    print 'a = {0}, b = {1}, c = {2}'.format(a,b,c)
mylist = ['aardvark', 'baboon', 'cat']
print_three_things(*mylist)

# use for subclass
class Foo(object):
    def __init__(self, value1, value2):
        print value1, value2
class MyFoo(Foo):
    def __init__(self, *args, **kwargs):
        print 'myfoo'
        super(MyFoo, self).__init__(*args, **kwargs)
