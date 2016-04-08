
apply vs call vs bind
==============================

**`apply`** and **`call`** are similar functions which sets `this` (context of a function).

The difference: how we send the arguments (manual vs array)

--------------------------------

**`bind`**: When you want that function to later be called with a certain context, useful in events.

**`Call/apply`** call the function immediately, whereas bind returns a function that when later executed will have the correct
context set for calling the original function. This way you can maintain context in async callbacks, and events.


```javascript
function MyObject(element) {
    this.elm = element;

    element.addEventListener('click', this.onClick.bind(this), false);
};

MyObject.prototype.onClick = function(e) {
     var t=this;  //do something with [t]...
    //without bind the context of this function wouldn't be a MyObject
    //instance as you would normally expect.
};
```

--------------------------------------------------------

- `bind()` allows us to easily set which specific object will be bound to _this_ when a function or method is invoked.

```js
 // This data variable is a global variable​
var data = [
    {name:"Samantha", age:12},
    {name:"Alexis", age:14}
]

var user = {
    // local data variable​
    data    :[
        {name:"T. Woods", age:37},
        {name:"P. Mickelson", age:43}
    ],
    showData:function (event) {
        var randomNum = ((Math.random () * 2 | 0) + 1) - 1; // random number between 0 and 1​
        console.log (this.data[randomNum].name + " " + this.data[randomNum].age);
    }
}

// Assign the showData method of the user object to a variable​
var showDataVar = user.showData;
showDataVar (); // Samantha 12 (from the global data array, not from the local data array)​
/*
This happens because showDataVar () is executed as a global function and use of this inside showDataVar ()
is bound to the global scope, which is the window object in browsers.
*/

 // Bind the showData method to the user object​
var showDataVar = user.showData.bind (user);
// Now the we get the value from the user object because the this keyword is bound to the user object​
showDataVar (); // P. Mickelson 43​
```

- `bind()` allow us to borrow methods

```js
// Here we have a cars object that does not have a method to print its data to the console​
var cars = {
    data:[
        {name:"Honda Accord", age:14},
        {name:"Tesla Model S", age:2}
    ]

}

// We can borrow the showData () method from the user object we defined in the last example.​
// Here we bind the user.showData method to the cars object we just created.​
cars.showData = user.showData.bind (cars);
cars.showData (); // Honda Accord 14​
```

One problem with this example is that we are adding a new method `showData` on the `cars` object and 
we might not want to do that just to borrow a method because the cars object might already have a property or method name `showData`.
We don’t want to overwrite it accidentally. As we will see in our discussion of `Apply` and `Call` below, 
it is best to borrow a method using either the `Apply` or `Call` method.

- `bind()` allow us to curry a function

[**Function Currying**](https://en.wikipedia.org/wiki/Currying), also known as _partial function application_, is the use of a
function (that accept one or more arguments) that returns a new function with some of the arguments already set. 

```js
function greet (gender, age, name) {
    // if a male, use Mr., else use Ms.​
    var salutation = gender === "male" ? "Mr. " : "Ms. ";
​
    if (age > 25) {
        return "Hello, " + salutation + name + ".";
    }
    else {
        return "Hey, " + name + ".";
    }
}
```

We can use `bind()` to curry this `greet` function

```js
// So we are passing null because we are not using the "this" keyword in our greet function.
var greetAnAdultMale = greet.bind (null, "male", 45);

greetAnAdultMale ("John Hartlove"); // "Hello, Mr. John Hartlove."

var greetAYoungster = greet.bind (null, "", 16);
greetAYoungster ("Alex"); // "Hey, Alex."​
greetAYoungster ("Emma Waterloo"); // "Hey, Emma Waterloo."
```

- `apply()` or `call()` to set _this_ value

The `apply`, `call`, and `bind` methods are all used to set the this value when invoking a method, and they do it in slightly
different ways to allow use direct control and versatility in our JavaScript code. 

The `apply` and `call` methods are almost identical when setting the this value except that you pass the function parameters to `apply ()` as _an array_, while you have to _list the parameters individually_ to pass them to the `call ()` method. 

Here is one example to use `call` or `apply` to set _this_ in the callback function.

```js
// Define an object with some properties and a method​
// We will later pass the method as a callback function to another function​
var clientData = {
    id: 094545,
    fullName: "Not Set",
    // setUserName is a method on the clientData object​
    setUserName: function (firstName, lastName)  {
        // this refers to the fullName property in this object​
        this.fullName = firstName + " " + lastName;
    }
};

function getUserInput (firstName, lastName, callback, callbackObj) {
    // The use of the Apply method below will set the "this" value to callbackObj​
    callback.apply (callbackObj, [firstName, lastName]);
}

// The clientData object will be used by the Apply method to set the "this" value​
getUserInput ("Barack", "Obama", clientData.setUserName, clientData);
// the fullName property on the clientData was correctly set​
console.log (clientData.fullName); // Barack Obama
```

- Borrow functions with `apply` or `call`

  - Borrow Array methods
  
    Let’s create an `array-like` object and borrow some array methods to operate on the our array-like object.
    
    ```js
    // An array-like object: note the non-negative integers used as keys​
    var anArrayLikeObj = {0:"Martin", 1:78, 2:67, 3:["Letta", "Marieta", "Pauline"], length:4 };
    
    // Make a quick copy and save the results in a real array:
    // First parameter sets the "this" value​
    var newArray = Array.prototype.slice.call (anArrayLikeObj, 0);
    console.log (newArray); // ["Martin", 78, 67, Array[3]]​

    // Search for "Martin" in the array-like object​
    console.log (Array.prototype.indexOf.call (anArrayLikeObj, "Martin") === -1 ? false : true); // true​
    // Try using an Array method without the call () or apply ()​
    console.log (anArrayLikeObj.indexOf ("Martin") === -1 ? false : true); // Error: Object has no method 'indexOf'
    ```

   Another common case is that convert `arguments` to array as following
   
   ```js
    // We do not define the function with any parameters, yet we can get all the arguments passed to it​
    function doSomething () {
        var args = Array.prototype.slice.call (arguments);
        console.log (args);
    }

    doSomething ("Water", "Salt", "Glue"); // ["Water", "Salt", "Glue"]
   ```

  - Borrow other methods

    ```js
    var gameController = {
        scores  :[20, 34, 55, 46, 77],
        avgScore:null,
        players :[
            {name:"Tommy", playerID:987, age:23},
            {name:"Pau", playerID:87, age:33}
        ]
    }
    var appController = {
        scores  :[900, 845, 809, 950],
        avgScore:null,
        avg     :function () {
            var sumOfScores = this.scores.reduce (function (prev, cur, index, array) {
                return prev + cur;
            });
            this.avgScore = sumOfScores / this.scores.length;
        }
    }
    // Note that we are using the apply () method, so the 2nd argument has to be an array​
    appController.avg.apply (gameController);
    console.log (gameController.avgScore); // 46.4​
    // appController.avgScore is still null; it was not updated, only gameController.avgScore was updated​
    console.log (appController.avgScore); // null​
    ```
    
- Use `apply()` to execute _variable-arity_ function

The [`Math.max`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/max) is one example of variable-arity function,

```js
// We can pass any number of arguments to the Math.max () method​
console.log (Math.max (23, 11, 34, 56)); // 56
```

But what if we have an array of numbers to pass to `Math.max`? We cannot do this:

```js
var allNumbers = [23, 11, 34, 56];
// We cannot pass an array of numbers to the the Math.max method like this​
console.log (Math.max (allNumbers)); // NaN
```	    

This is where the `apply ()` method helps us execute _variadic functions_. Instead of the above, we have to pass the array of numbers using `apply (`) thus:

```js
var allNumbers = [23, 11, 34, 56];
// Using the apply () method, we can pass the array of numbers:
console.log (Math.max.apply (null, allNumbers)); // 56
```    
    
-------------------------------------------


Ref:

[1](http://javascriptissexy.com/javascript-apply-call-and-bind-methods-are-essential-for-javascript-professionals/)
[2](http://stackoverflow.com/questions/15455009/javascript-call-apply-vs-bind)

