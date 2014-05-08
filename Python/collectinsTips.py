# check whether a list is empty
if mylist:
    # Do something with my list
else:
    # The list is empty
    
#Getting indexes of elements while iterating over a list
for i, element in enumerate(mylist):
    # Do something with i and element
    pass
    
# sort a list
class Person(object):
    def __init__(self, age):
        self.age = age

persons = [Person(age) for age in (14, 78, 42)]
from operator import attrgetter

for element in sorted(persons, key=attrgetter('age')):
    print "Age:", element.age

#Grouping elements in a dictionary
from collections import defaultdict

persons_by_age = defaultdict(list)

for person in persons:
    persons_by_age[person.age].append(person)
