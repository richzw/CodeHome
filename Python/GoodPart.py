'''
So for example I have

'ab@cde@@fghi@jk@lmno@@@p@qrs@tuvwxy@z'

and want

'ab1cde23fghi1jk2lmno312p3qrs1tuvwxy2z'

for replace_chars = ['1', '2', '3']
'''

>>> from itertools import cycle
>>> s = 'ab@cde@@fghi@jk@lmno@@@p@qrs@tuvwxy@z'
>>> replace_chars = ['1', '2', '3']
>>>
>>> replacer = cycle(replace_chars)
>>> ''.join([next(replacer) if c == '@' else c for c in s])
'ab1cde23fghi1jk2lmno312p3qrs1tuvwxy2z'



# Get odd index from list
>>> a = [1,2,3,4,5,6,7,8]
>>> for i in xrange(len(a)):
	    if i & 0x1:
		    a.pop(i)  
IndexError: pop index out of range
# correct way
>>> a = [1,2,3,4,5,6,7,8]
>>> a = a[::2]

# object and reference
>>> a = [1, 2]
>>> id(a)
50178376L
>>> a.extend([3])
>>> id(a)
50178376L
>>> a += [4]
>>> id(a)
50178376L
>>> a = a + [5]
>>> id(a)
50179016L
>>> a
[1, 2, 3, 4, 5]

# list in tuple
>>> a = ([], [])
>>> a[0].append(1)
>>> a[0].extend([2])
>>> a[0] += [3]

Traceback (most recent call last):
  File "<pyshell#529>", line 1, in <module>
    a[0] += [3]
TypeError: 'tuple' object does not support item assignment
>>> a
([1, 2, 3], [])

# deepcopy
>>> from copy import deepcopy
>>> a = [1, 2, 3]
>>> b = deepcopy(a)
>>> b.append(5)
>>> id(a), id(b), a, b
(50178504L, 49313032L, [1, 2, 3], [1, 2, 3, 5])
>>> c = a[:]
>>> id(a), id(b), id(c)
(50178504L, 49313032L, 50177992L)

#init value of function parameters
>>> class A:
    b = []
    def __init__(self, c):
        self.b.append(c)

>>> f = A(1)
>>> g = A(2)
>>> f.b, g.b
([1, 2], [1, 2])

def func(b=None):
  b = b or []
  ...
  
# closure hard part
>>> a = []
>>> for i in xrange(10):
	def b():
		return i
	a.append(b)
	
fix it
a.append(b())

# attention: issue happened at multi-thread invironment!!!!!






