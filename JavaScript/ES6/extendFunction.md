
### Question

ES6 allows to extend special objects. So it's possible to inherit from the function. Such object can be called as a function, 
but how can I implement the logic for such call?

```javascript
class Smth extends Function {
  constructor (x) {
    // What should be done here
    super();
  }
}

(new Smth(256))() // to get 256 at this call?
```

### Answer

The `super` call will invoke the `Function constructor`, which expects a code string. If you want to access your instance data, 
you could just hardcode it:

```javascript
class Smth extends Function {
  constructor(x) {
    super("return "+JSON.stringify(x)+";");
  }
}
```

but that's not really satisfying. We want to use a **closure**.

Having the returned function be a closure that can access your instance variables is possible, but not easy. 
The good thing is that you don't have to call `super` if you don't want to - you still can `return` arbitrary objects from
your ES6 class constructors. In this case, we'd do

```javascript
class Smth extends Function {
  constructor(x) {
    // refer to `smth` instead of `this`
    function smth() { return x; };
    Object.setPrototypeOf(smth, Smth.prototype);
    return smth;
  }
}
```

But we can do even better, and abstract this thing out of `Smth`:

```javascript
class ExtensibleFunction extends Function {
  constructor(f) {
    return Object.setPrototypeOf(f, new.target.prototype);
  }
}

class Smth extends ExtensibleFunction {
  constructor(x) {
    super(function() { return x; }); // closure
    // console.log(this); // function() { return x; }
    // console.log(this.prototype); // {constructor: …}
  }
}
class Anth extends ExtensibleFunction {
  constructor(x) {
    super(() => { return this.x; }); // arrow function, no prototype object created
    this.x = x;
  }
}
class Evth extends ExtensibleFunction {
  constructor(x) {
    super(function f() { return f.x; }); // named function
    this.x = x;
  }
}
```

Admittedly, this creates an additional level of indirection in the inheritance chain, but that's not necessarily a bad thing
(you can extend it instead of the native Function). If you want to avoid it, use

```javascript
function ExtensibleFunction(f) {
  return Object.setPrototypeOf(f, new.target.prototype);
}
ExtensibleFunction.prototype = Function.prototype;
```

but notice that `Smth` will not dynamically inherit `static Function` properties.

### Source

[How to extend function in ES6](http://stackoverflow.com/questions/36871299/how-to-extend-function-with-es6-classes)

