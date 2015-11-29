
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




