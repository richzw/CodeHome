
[Source](http://dmitryfrank.com/articles/js_closures)

-----------------------------------

```javascript
"use strict";
var foo = 1;
var bar = 2;
 
function myFunc() {
  //-- define local-to-function variables
  var a = 1;
  var b = 2;
  var foo = 3;
 
  console.log("inside myFunc");
}
 
console.log("outside");
 
//-- and then, call it:
myFunc();
```

![](http://dmitryfrank.com/_media/articles/js_closure_3.png)


```javascript
"use strict";
 
function createCounter(initial) {
  //-- define local-to-function variables
  var counter = initial;
 
  //-- define nested functions. Each of them will have
  //   a reference to the current scope object
 
  /**
   * Increments internal counter by given value.
   * If given value is not a finite number or is less than 1, then 1 is used.
   */
  function increment(value) {
    if (!isFinite(value) || value < 1){
      value = 1;
    }
    counter += value;
  }
 
  /**
   * Returns current counter value.
   */
  function get() {
    return counter;
  }
 
 
  //-- return object containing references
  //   to nested functions
  return {
    increment: increment,
    get: get
  };
}
 
//-- create counter object
var myCounter = createCounter(100);
 
console.log(myCounter.get());   //-- prints "100"
 
myCounter.increment(5);
console.log(myCounter.get());   //-- prints "105"

```

![](http://dmitryfrank.com/_media/articles/js_closure_6_inc.png)



