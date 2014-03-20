class Human(object):
    def __init__(self, weight):
        self.weight = weight
    def get_weight(self):
        return self.weight


In [10]: Human.get_weight(Human(45))
Out[10]: 45

In [11]: person = Human(45)
In [12]: person.get_weight()
Out[12]: 45
