### Question

```js
function1 = function(){
  var variable = "foo"
  var function2 = function(argument){
    console.log(variable + argument);
  }
  return function2
}

function3 = function1();
function3("bar");
```

### Answer

Whenever a function is executed a new **lexical environment** is created. The environment has _two "fields"_: 
- an environment record where all the variables are being tracked
- a outer lexical environment that refers to, as the name suggested, to the "parent lexical environment".

So when we your code example is evaluated, the initial state of the memory (before executing anything) might look like this (simplified):

```
+-(Global) lexical environment-+     +-Environment Record-+
+-------------+----------------+     +---------+----------+
| Environment |       *--------+---> |function1|undefined |
|   Record    |                |     +---------+----------+
+-------------+----------------+     |function3|undefined |
|    Outer    |                |     +---------+----------+
|   lexical   |    (empty)     |
| environment |                |
+-------------+----------------+
```

The global environment doesn't have any outer environment because it is at the top. `function1` and `function3` are two bindings that
haven't been initialized yet (the assignment wasn't evaluated yet).

After creating the function (evaluating `function1 = function() { ... }`), the memory looks like this:

```
            +------------------------------------------------------------------------+
            |                                                                        |
            v                                                                        |
+-(Global) lexical environment-+    +-Environment Record-+     +-----Function Object-+---+
+-------------+----------------+    +---------+----------+     +---------------+-----+---+
| Environment |       *--------+--->|function1|    *-----+---->|[[Environment]]|     *   |
|   Record    |                |    +---------+----------+     +---------------+---------+
+-------------+----------------+    |function3|undefined |     |     name      |function1|
|    Outer    |                |    +---------+----------+     +---------------+---------+
|   lexical   |    (empty)     |
| environment |                |
+-------------+----------------+
```

Now function1 has a value, a function object. Function objects have multiple internal (e.g. `[[Environment]]`) and external (e.g. name)
properties. As the name implies, internal properties cannot be accessed from user code. The `[[Environment]]` property is very important.
Notice how it refers back to the lexical environment the function was created in!

The next step is executing `function3 = function1()`, i.e. calling `function2`. As I said at the very beginning, whenever a function is
executed a new lexical environment is created. Let's look at the memory just after entering the function:

```
               +------------------------------------------------------------------------+
               |                                                                        |
               v                                                                        |
   +-(Global) lexical environment-+    +-Environment Record-+     +-----Function Object-+---+
   +-------------+----------------+    +---------+----------+     +---------------+-----+---+
   | Environment |       *--------+--->|function1|          +---->|[[Environment]]|     *   |
   |   Record    |                |    +---------+----------+     +---------------+---------+
+> +-------------+----------------+    |function3|undefined |     |     name      |function1|
|  |    Outer    |                |    +---------+----------+     +---------------+---------+
|  |   lexical   |    (empty)     |
|  | environment |                |
|  +-------------+----------------+
|
|
|
|  +-----lexical environment------+    +-Environment Record-+
|  +-------------+----------------+    +---------+----------+
|  | Environment |       *--------+--->|variable |undefined |
|  |   Record    |                |    +---------+----------+
|  +-------------+----------------+    |function2|undefined |
|  |    Outer    |                |    +---------+----------+
|  |   lexical   |        *       |
|  | environment |        |       |
|  +-------------+--------+-------+
|                         |
+-------------------------+
```

This looks very similar to the structure of the global environment! We have a lexical environment that has an environment record with
two unintialized bindings. But the big difference now is that "outer lexical environment" points to the global lexical environment. 
How is that possible?

When calling function1 and creating a new lexical environment, we set the value of the new environments "outer lexical environment" field to the value of function1's [[Environment]] field. This is were the scope chain is created.

Now, after executing function1, the memory has this structure:

```
               +------------------------------------------------------------------------+
               |                                                                        |
               v                                                                        |
   +-(Global) lexical environment-+    +-Environment Record-+     +-----Function Object-+---+
   +-------------+----------------+    +---------+----------+     +---------------+-----+---+
   | Environment |       *--------+--->|function1|    *-----+---->|[[Environment]]|     *   |
   |   Record    |                |    +---------+----------+     +---------------+---------+
+> +-------------+----------------+    |function3|   |      |     |     name      |function1|
|  |    Outer    |                |    +---------+---+------+     +---------------+---------+
|  |   lexical   |    (empty)     |                  |
|  | environment |                |                  |
|  +-------------+----------------+                  +-------------------------+
|                                                                              |
|             +----------------------------------------------------------------+--------+
|             v                                                                |        |
|  +-----lexical environment------+    +-Environment Record-+                  v        |
|  +-------------+----------------+    +---------+----------+                           |
|  | Environment |       *--------+--->|variable |  'foo'   |     +-----Function Object-+---+
|  |   Record    |                |    +---------+----------+     +---------------+-----+---+
|  +-------------+----------------+    |function2|    *-----+---->|[[Environment]]|     *   |
|  |    Outer    |                |    +---------+----------+     +---------------+---------+
|  |   lexical   |        *       |                               |     name      |function2|
|  | environment |        |       |                               +---------------+---------+
|  +-------------+--------+-------+
|                         |
+-------------------------+
```

Similar like `function1`, `function2` has a reference to the environment created by calling `function2`. In addition, `function3` refers
to the function we created because we return it from `function1`.

Last step: calling `function3('bar')`:

```
               +------------------------------------------------------------------------+
               |                                                                        |
               v                                                                        |
   +-(Global) lexical environment-+    +-Environment Record-+     +-----Function Object-+---+
   +-------------+----------------+    +---------+----------+     +---------------+-----+---+
   | Environment |       *--------+--->|function1|    *-----+---->|[[Environment]]|     *   |
   |   Record    |                |    +---------+----------+     +---------------+---------+
+> +-------------+----------------+    |function3|   |      |     |     name      |function1|
|  |    Outer    |                |    +---------+---+------+     +---------------+---------+
|  |   lexical   |    (empty)     |                  |
|  | environment |                |                  |
|  +-------------+----------------+                  +-------------------------+
|                                                                              |
|             +----------------------------------------------------------------+--------+
|             v                                                                |        |
|  +-----lexical environment------+    +-Environment Record-+                  v        |
|  +-------------+----------------+    +---------+----------+                           |
|  | Environment |       *--------+--->|variable |  'foo'   |     +-----Function Object-+---+
|  |   Record    |                |    +---------+----------+     +---------------+-----+---+
|+>+-------------+----------------+    |function2|    *-----+---->|[[Environment]]|     *   |
|| |    Outer    |                |    +---------+----------+     +---------------+---------+
|| |   lexical   |        *       |                               |     name      |function2|
|| | environment |        |       |                               +---------------+---------+
|| +-------------+--------+-------+
++------------------------+
 |
 | +-----lexical environment------+    +-Environment Record-+
 | +-------------+----------------+    +---------+----------+
 | | Environment |       *--------+--->|argument |  'bar'   |
 | |   Record    |                |    +---------+----------+
 | +-------------+----------------+
 | |    Outer    |                |
 | |   lexical   |        *       |
 | | environment |        |       |
 | +-------------+--------+-------+
 +------------------------+
```

Similar here, a new environment is created and its "outer lexical environment" field points to the environment created when `function1`
was called.

### Source

[1](http://stackoverflow.com/questions/37491626/where-does-a-javascript-closure-live)
