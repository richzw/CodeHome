
----------------------------------

The `this` reference ALWAYS refers to (and holds the value of) an object—a singular object—and it is usually used inside a function or
a method, although it can be used outside a function in the global scope. 

_Note that when we use **strict mode**, this holds the value of undefined in global functions and in anonymous functions that
are not bound to any object._

----------------------------------------

- _Fix this when used in a method passed as a callback_

```javascript
    // We have a simple object with a clickHandler method that we want to use when a button on the page is clicked​
    var user = {
    data:[
    {name:"T. Woods", age:37},
    {name:"P. Mickelson", age:43}
    ],
    clickHandler:function (event) {
    var randomNum = ((Math.random () * 2 | 0) + 1) - 1; // random number between 0 and 1​
​
    // This line is printing a random person's name and age from the data array​
    console.log (this.data[randomNum].name + " " + this.data[randomNum].age);
    }
    }
​
    // The button is wrapped inside a jQuery $ wrapper, so it is now a jQuery object​
    // And the output will be undefined because there is no data property on the button object​
    $ ("button").click (user.clickHandler); // Cannot read property '0' of undefined
```

**Solution**: Since we really want this.data to refer to the data property on the user object, 
we can use the `Bind ()`, `Apply ()`, or `Call ()` method to specifically set the value of this.

` $("button").click (user.clickHandler.bind (user)); // P. Mickelson 43`

- _Fix this inside closure_

```javascript
var user = {
    tournament:"The Masters",
    data      :[
    {name:"T. Woods", age:37},
    {name:"P. Mickelson", age:43}
    ],
​
    clickHandler:function () {
    // the use of this.data here is fine, because "this" refers to the user object, and data is a property on the user object.​
​
    this.data.forEach (function (person) {
    // But here inside the anonymous function (that we pass to the forEach method), "this" no longer refers to the user object.​
    // This inner function cannot access the outer function's "this"​
   
    console.log ("What is This referring to? " + this); //[object Window]​
 
    console.log (person.name + " is playing at " + this.tournament);
    // T. Woods is playing at undefined​
    // P. Mickelson is playing at undefined​
    })
    }
​
    }
​
    user.clickHandler(); // What is "this" referring to? [object Window]
```

**Solution**: maintain this inside anonymous functions

```javascript
var user = {
    tournament:"The Masters",
    data      :[
    {name:"T. Woods", age:37},
    {name:"P. Mickelson", age:43}
    ],
​
    clickHandler:function (event) {
    // To capture the value of "this" when it refers to the user object, we have to set it to another variable here:​
    // We set the value of "this" to theUserObj variable, so we can use it later​
    var theUserObj = this;
    this.data.forEach (function (person) {
    // Instead of using this.tournament, we now use theUserObj.tournament​
    console.log (person.name + " is playing at " + theUserObj.tournament);
    })
    }
​
    }
​
    user.clickHandler();
```

- _Fix this when method is assigned to a variable_

```javascript
 // This data variable is a global variable​
    var data = [
    {name:"Samantha", age:12},
    {name:"Alexis", age:14}
    ];
​
    var user = {
    // this data variable is a property on the user object​
    data    :[
    {name:"T. Woods", age:37},
    {name:"P. Mickelson", age:43}
    ],
    showData:function (event) {
    var randomNum = ((Math.random () * 2 | 0) + 1) - 1; // random number between 0 and 1​
​
    // This line is adding a random person from the data array to the text field​
    console.log (this.data[randomNum].name + " " + this.data[randomNum].age);
    }
​
    }
​
    // Assign the user.showData to a variable​
    var showUserData = user.showData;
​
    // When we execute the showUserData function, the values printed to the console are from the global data array, not from the data array in the user object​
    //​
    showUserData (); // Samantha 12 (from the global data array)​
```

**Solution**: maintaining this when method is assigned to a variable

```javascript
 // Bind the showData method to the user object​
    var showUserData = user.showData.bind (user);
​
    // Now we get the value from the user object, because the <em>this</em> keyword is bound to the user object​
    showUserData (); // P. Mickelson 43
```

--------------------------------------------------------

- **gloabl this**

- In a browser, at the global scope, `this` is the `window `object

```javascript
<script type="text/javascript">
    console.log(this === window); // true
    var foo = "bar";
    console.log(this.foo); // "bar"
    console.log(window.foo); // "bar"
</script>
```

- In node using the repl, `this` is the top namespace. You can refer to it as `global`.

```javascript
> this
{ ArrayBuffer: [Function: ArrayBuffer],
  Int8Array: { [Function: Int8Array] BYTES_PER_ELEMENT: 1 },
  Uint8Array: { [Function: Uint8Array] BYTES_PER_ELEMENT: 1 },
  ...
> global === this
true
```

- In node executing from a script, `this` at the global scope starts as an empty object. It is not the same as `global`

```javascript
\\ test.js
console.log(this);  \\ {}
console.log(this === global); \\ fasle
```

- **function this**

Except in the case of DOM event handlers or when a `thisArg` is provided (see further down), both in node and in a browser using `this` in a function that is not called with `new` references the global scope…

```javascript
<script type="text/javascript">
    foo = "bar";

    function testThis() {
      this.foo = "foo";
    }

    console.log(this.foo); //logs "bar"
    testThis();
    console.log(this.foo); //logs "foo"
</script>
```

If you use `use strict;`, in which case `this` will be `undefined`

```javascript
<script type="text/javascript">
    foo = "bar";

    function testThis() {
      "use strict";
      this.foo = "foo";
    }

    console.log(this.foo); //logs "bar"
    testThis();  //Uncaught TypeError: Cannot set property 'foo' of undefined 
</script>
```

If you call a function with `new` the `this` will be a new context, it will not reference the global `this`.

```javascript
<script type="text/javascript">
    foo = "bar";

    function testThis() {
      this.foo = "foo";
    }

    console.log(this.foo); //logs "bar"
    new testThis();
    console.log(this.foo); //logs "bar"

    console.log(new testThis().foo); //logs "foo"
</script>
```

- **prototype this**

Functions you create become function objects. They automatically get a special `prototype` property, which is something you can assign values to. When you create an instance by calling your function with `new` you get access to the values you assigned to the `prototype` property. You access those values using `this`.

```javascript
    function Thing() {
      console.log(this.foo);
    }

    Thing.prototype.foo = "bar";

    var thing = new Thing(); //logs "bar"
    console.log(thing.foo);  //logs "bar"
```

It is usually a mistake to assign _arrays_ or _objects_ on the `prototype`. If you want instances to each have their own arrays, create them in the function, not the prototype.

```javascript
function Thing() {
    this.things = [];
}


var thing1 = new Thing();
var thing2 = new Thing();
thing1.things.push("foo");
console.log(thing1.things); //logs ["foo"]
console.log(thing2.things); //logs []
```

- **object this**

You can use `this` in any function on an object to refer to other properties on that object. This is not the same as an instance created with `new`.

```javascript
var obj = {
    foo: "bar",
    logFoo: function () {
        console.log(this.foo);
    }
};

obj.logFoo(); //logs "bar"
```

- **DOM event this**

In an HTML DOM event handler, `this` is always a reference to the DOM element the event was attached to 

```javascript
function Listener() {
    document.getElementById("foo").addEventListener("click",
       this.handleClick);
}
Listener.prototype.handleClick = function (event) {
    console.log(this); //logs "<div id="foo"></div>"
}

var listener = new Listener();
document.getElementById("foo").click();
```

Unless you `bind` the context

```javascript
function Listener() {
    document.getElementById("foo").addEventListener("click", 
        this.handleClick.bind(this));
}
Listener.prototype.handleClick = function (event) {
    console.log(this); //logs Listener {handleClick: function}
}

var listener = new Listener();
document.getElementById("foo").click();
```

- **HTML this**

Inside HTML attributes in which you can put JavaScript, `this` is a reference to the element. 

```javascript
<div id="foo" onclick="console.log(this);"></div>
<script type="text/javascript">
document.getElementById("foo").click(); //logs <div id="foo"...
</script>
```

- **eval this**

You can use `eval` to access `this`.

```javascript
function Thing () {
}
Thing.prototype.foo = "bar";
Thing.prototype.logFoo = function () {
    eval("console.log(this.foo)"); //logs "bar"
}

var thing = new Thing();
thing.logFoo(); 
```

- **with this**

You can use `with` to add `this` to the current scope to read and write to values on `this` without referring to `this` explicitly.

```javascript
function Thing () {
}
Thing.prototype.foo = "bar";
Thing.prototype.logFoo = function () {
    with (this) {
        console.log(foo);
        foo = "foo";
    }
}

var thing = new Thing();
thing.logFoo(); // logs "bar"
console.log(thing.foo); // logs "foo"
```

- **jQuery this**

the jQuery will in many places have `this` refer to a DOM element. 

```javascript
<div class="foo bar1"></div>
<div class="foo bar2"></div>
<script type="text/javascript">
$(".foo").each(function () {
    console.log(this); //logs <div class="foo...
});
$(".foo").on("click", function () {
    console.log(this); //logs <div class="foo...
});
$(".foo").each(function () {
    this.click();
});
</script>
```

// Source: http://bjorn.tipling.com/all-this
