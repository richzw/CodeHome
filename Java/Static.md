### Question

```java
public class Test {
    public static final Test me = new Test();
    public static final Integer I = 4;
    public static final String S = "abc";

    public Test() {
        System.out.println(I);
        System.out.println(S);
    }

    public static Test getInstance() { return me; }

    public static void main(String[] args) {
        Test.getInstance();
    }
} 
```

When we run the main method, we get a result of:

```java
null
abc
```

I would understand if it wrote `null` values both times, since the code of static class members is executed from top to bottom.

### Answer

These are the steps taken when you run your program:

- Before main can be run, the Test class must be initialized by running static initializers in order of appearance.
- To initialize the me field, start executing `new Test()`.
- Print the value of `I`. Since the field type is Integer, what seems like a compile-time constant `4` becomes a computed value 
(`Integer.valueOf(4)`). The initializer of this field has not yet run, printing the initial value null.
- Print the value of `S`. Since it is initialized with a compile-time constant, this value is baked into the referencing site, 
printing `abc`.
- `new Test()` completes, now the initializer for `I` executes.

Lesson: if you rely on eagerly initialized static singletons, place the singleton declaration as the last static field declaration, 
or resort to a static initializer block that occurs after all other static declarations. That will make the class appear fully 
initialized to the singleton's construction code.

