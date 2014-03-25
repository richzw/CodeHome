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
