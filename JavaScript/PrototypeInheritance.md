JavaScript Prototype
----------

                                   Inheritance
                                        |
                         +-----------------------------+
                         |                                |
                         v                                v
                    Prototypal                       Classical
                         |
         +------------------------------+
         |                                 |
         v                                 v
    Prototypal Pattern               Constructor Pattern


**Object-oriented programming**

Objects are simply abstractions which encapsulate the properties of a real world entity 
(i.e. they represent real word things in the program).

- **Abstraction**: The representation of real world things in computer programs.
- **Generalization**: An abstraction of a more specific abstraction.

object-oriented programming we create objects (which are abstractions of real world entities) and we use either classes
or prototypes to create generalizations of these objects. Generalizations are created via inheritance

**Classical object-oriented programming**

classical object-oriented programming we have two types of abstractions: classes and objects. An object, 
as mentioned before, is an abstraction of a real world entity. A class on the other hand is an abstraction 
of an object or another class (i.e. it's a generalization)
Objects in classical object-oriented programming languages can only be created by instantiating classes:
In summation in classical object-oriented programming languages objects are abstractions of real world entities and 
classes are generalizations

Prototype object-oriented programming
As you can see in prototypal object-oriented programming languages objects are abstractions of either 
real world entities (in which case they are simply called objects) or other objects 
(in which case they are called prototypes of those objects that they abstract). Hence a prototype is a generalization.
Objects in prototypal object-oriented programming languages may be created either ex-nihilo (i.e. out of nothing) 
or from another object (which becomes the prototype of the newly created object):

```javascript
var human = {};
var man = Object.create(human);
var johnDoe = Object.create(man);
```

In my humble opinion prototypal object-oriented programming languages are more powerful than classical object-oriented
programming languages because:

- There is only one type of abstraction.
- Generalizations are simply objects.

By now you must have realized the difference between classical inheritance and prototypal inheritance. 
Classical inheritance is limited to classes inheriting from other classes. However prototypal inheritance 
includes not only prototypes inheriting from other prototypes but also objects inheriting from prototypes.

The prototype system offers a captivating model of metaprogramming, by implementing inheritance via standard objects. 
Of course, this is mostly used to express the established and simple concept of classes of instances, 
but without classes as language-level immutable structures that need specific syntax to create them. 
By using plain objects, all you can do to objects (and you can do everything) you can now do to "classes" - 
this is the flexibility you talk of.

This flexibility is then used a lot to extend and alter classes programmatically, using only the given object-mutation
capabilities of JavaScript:

- mixins and traits for multiple inheritance
- prototypes can be modified after objects that inherit from them have been instantiated
- higher-order functions and method decorators can be used easily in the creation of prototypes

Benefit of prototype:
------------

**1.Prototype inheritance is simple**

Hence we only need two things to make prototypal inheritance work:

- A way to create a new object (e.g. object literals).
- A way to extend an existing object (e.g. Object.create).

In contrast classical inheritance is much more complicated. In classical inheritance you have:

- Classes.
- Object.
- Interfaces.
- Abstract Classes.
- Final Classes.
- Virtual Base Classes.
- Constructors.
- Destructors.

**2.Prototype inheritance is powerful**

Most programmers who come from a classical background argue that classical inheritance is more powerful than 
prototypal inheritance because it has:

- Private variables.
- Multiple inheritance.

This claim is false. We already know that JavaScript supports private variables via closures, but what about multiple
inheritance? Objects in JavaScript only have one prototype.

The truth is that prototypal inheritance supports inheriting from multiple prototypes. Prototypal inheritance simply
means one object inheriting from another object. There are actually two ways to implement prototypal inheritance:

- Delegation or Differential Inheritance
- Cloning or Concatenative Inheritance

**3.Prototype inheritance is less redundant**

Since prototypal inheritance allows for multiple inheritance, code which requires multiple inheritance is less
redundant if written using prototypal inheritance rather than in a language which has classical inheritance 
but no multiple inheritance.

**4.Prototype inheritance is dynamic**

One of the most important advantages of prototypal inheritance is that you can add new properties to prototypes 
after they are created. This allows you to add new methods to a prototype which will be automatically made available
to all the objects which delegate to that prototype.


**Ref:**

http://stackoverflow.com/questions/28783077/what-can-the-javascript-prototype-system-do-beyond-mimicking-a-classical-class-s#

http://stackoverflow.com/questions/19633762/classical-inheritance-vs-protoypal-inheritance-in-javascript/19640910#19640910

http://stackoverflow.com/questions/2800964/benefits-of-prototypal-inheritance-over-classical#


