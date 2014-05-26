"""
To understand what yield does, you must understand what generators are. And before generators come iterables.

Iterable:
>>> mylist = [x*x for x in range(3)]
>>> for i in mylist:
...    print(i)
0
1
4
Everything you can use "for... in..." on is an iterable: lists, strings, files... These iterables are handy 
because you can read them as much as you wish, but you store all the values in memory and it's not always 
what you want when you have a lot of values.

Generator:
Generators are iterators, but you can only iterate over them once. 
It's because they do not store all the values in memory, they generate the values on the fly:
>>> mygenerator = (x*x for x in range(3))
>>> for i in mygenerator:
...    print(i)
0
1
4

Yield:
Yield is a keyword that is used like return, except the function will return a generator.
>>> def createGenerator():
...    mylist = range(3)
...    for i in mylist:
...        yield i*i
...
>>> mygenerator = createGenerator() # create a generator
>>> print(mygenerator) # mygenerator is an object!
<generator object createGenerator at 0xb7555c34>
>>> for i in mygenerator:
...     print(i)
0
1
4
To master yield, you must understand that when you call the function, 
the code you have written in the function body does not run. The function only returns the generator object, 

The first time the for calls the generator object created from your function, 
it will run the code in your function from the beginning until it hits yield, 
then it'll return the first value of the loop. Then, each other call will run the loop you have written in the function 
one more time, and return the next value, until there is no value to return.

"""



# tree tranverse 
 # wrong version
 def traverse_wrong(node):          
     if isinstance(node, list):     
         for sub_node in node:       
             traverse_wrong(sub_node)    #it only create another generator, not invoke it.
     else:                            
         yield node                  
   
 # right version: 
 def traverse_right(node):            
     if isinstance(node, list):      
         for sub_node in node:      
             for sub_result in traverse_right(sub_node): # another coroutine tranverse the nodes
                 yield sub_result                        # current coroutine just convey the result of coroutine 
     else:                           
         yield node                  
   
 # Python3.3
 def traverse_right2(node):           
     if isinstance(node, list):      
         for sub_node in node:        
             yield from traverse_right2(sub_node)    
     else:                           
         yield node    
 # how to use yield
 # yield is called generator before
 #version 1
 def fab(max):
     n, a, b = 0, 0, 1
     while n < max:
         print b
         a, b = b, a+b
         n = n + 1
 #version 2
 def fab(max):
     n, a, b = 0, 0, 1
     L = []
     while n < max:
         L.append(b)
         a, b = b, a+b
         n = n + 1
     return L
#version 3, iterator
class Fab(object):
    def __init__(self, max):
        self.max = max
        self.n, self.a, self.b = 0, 0, 1
    def __iter__(self):
        return self
    def next(self):
        if self.n < self.max:
            r = self.b
            self.a, self.b = self.b, self.a+ self.b
            self.n = self.n + 1
            return r
        raise StopIteration()
for n in Fab(5):
    print n
   
#version 4, yield
def fab(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a+b
        n = n + 1
 for n in fab(5):
     print n
'''
 >>> f = fab(5) 
>>> f.next() 
1
>>> f.next() 
1
>>> f.next() 
2
>>> f.next() 
3
>>> f.next() 
5
>>> f.next() 
Traceback (most recent call last): 
 File "<stdin>", line 1, in <module> 
StopIteration    
'''  
