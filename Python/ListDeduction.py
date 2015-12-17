#comprehensions
num = [1,3,-5, 10, -9, 2, 5, -1]
filtered_and_squared = []
for number in num:
    if number > 0:
        filtered_and_squared.append(number**2)
print filtered_and_squared

# better
filtered_and_squared = map(lambda x: x**2, filter(lambda x: x > 0, num))

''' even better - list comprehension
[issue: load the whole list into memory ]'''
filtered_and_squared = [ x**2 for x in num if x > 0]

# best - Generator
filtered_and_squared = (x**2 for x in num if x > 0)

for item in filtered_and_squared:
    print item

# improvement
def square_generator(optional_parameter):
    return (x**2 for x in num if x > optional_parameter)

#option 1
for k in square_generator(0):
    print k
#option 2
g = list(square_generator(0))

'''
I have a list say l = [10,10,20,15,10,20]. I want to assign each unique value a certain "index" to get [1,1,2,3,1,2].
'''
>>> from itertools import count
>>> from collections import defaultdict
>>> lst = [10, 10, 20, 15, 10, 20]
>>> d = defaultdict(count(1).next)
>>> [d[k] for k in lst]
[1, 1, 2, 3, 1, 2]

'''
The default_factory(i.e count(1).next in this case) passed to defaultdict is called only when Python encounters a missing key, 
so for 10 the value is going to be 1, then for the next ten it is not a missing key anymore hence the previously calculated 1 is used, 
now 20 is again a missing key and Python will call the default_factory again to get its value and so on.
'''
