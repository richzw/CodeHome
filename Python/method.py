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


In [10]: Human.get_weight(Human(45))
Out[10]: 45

In [11]: person = Human(45)
In [12]: person.get_weight()
Out[12]: 45
