
[Java pass by value](http://javadude.com/articles/passbyvalue.htm)

- **Pass-by-value**
  
  The actual parameter (or argument expression) is fully evaluated and the resulting value is **copied** into a location being used to hold the formal parameter's value during method/function execution. That location is typically a chunk of memory on the runtime stack for the application (which is how Java handles it), but other languages could choose parameter storage differently.
- **Pass-by-reference**
  
  The formal parameter merely acts as an **alias** for the actual parameter. Anytime the method/function uses the formal parameter (for reading or writing), it is actually using the actual parameter.

```java
public void foo(Dog someDog) {
    someDog.setName("Max");     // AAA
    someDog = new Dog("Fifi");  // BBB
    someDog.setName("Rowlf");   // CCC
}

Dog myDog;

Dog myDog = new Dog("Rover");
foo(myDog);
```

Let's look at what's happening.

the parameter someDog is set to the value `42`

- at line "AAA"
  
  someDog is followed to the Dog it points to (the Dog object at address 42) that Dog (the one at address 42) is asked to change his name to Max
- at line "BBB"

  a new Dog is created. Let's say he's at address 74 we assign the parameter someDog to 74
- at line "CCC"
  
  someDog is followed to the Dog it points to (the Dog object at address 74) that Dog (the one at address 74) is asked to change his name to Rowlf then, we return

Now let's think about what happens outside the method: Did myDog change?

There's the key.

Keeping in mind that myDog is a pointer, and not an actual Dog, the answer is NO. myDog still has the value 42; it's still pointing to the original Dog.

