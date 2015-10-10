
apply vs call vs bind
==============================

**`apply`** and **`call`** are similar functions which sets `this` (context of a function).

The difference: how we send the arguments (manual vs array)

--------------------------------

**`bind`**: When you want that function to later be called with a certain context, useful in events.

`Call/apply` call the function immediately, whereas bind returns a function that when later executed will have the correct
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

-------------------------------------------


Ref:

[1](http://javascriptissexy.com/javascript-apply-call-and-bind-methods-are-essential-for-javascript-professionals/)

