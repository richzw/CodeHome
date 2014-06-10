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
