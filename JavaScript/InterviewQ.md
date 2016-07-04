
[25 enssential question](https://www.toptal.com/javascript/interview-questions)

--------------------------------------------------------------------------------

```javascript
Number.isInteger = Number.isInteger || function(value) {
    return typeof value === "number" && 
           isFinite(value) && 
           Math.floor(value) === value;
};
```

```javascript
function isPalindrome(str) {
    str = str.replace(/\W/g, '').toLowerCase();
    return (str == str.split('').reverse().join(''));
}
```

------------------------------------------------------------------

### Question

```js
(function(){
    return typeof arguments;
})();
```

Answer: **object**;

- `arguments` is not an array, it is an array-like object. 
- Even if `arguments` were a true array, the answer would still be `object`, because array are objects too.

----------------------------------------------------------------

### Question

```js
var foo = {
    bar: function() { return this.baz; },
    baz: 1
};

(function() {
    return typeof arguments[0]();
})(foo.bar);            // 'undefined'

typeof (f = foo.bar)(); // 'undefined'
```

Answer: 'undefined'.

Because `this` refers to the current context object, so `this` refers to different things depending on how a function is called. 
When we call `foo.bar` with the name `arguments[0]`, `this` in `foo.bar` is not bound to `foo`, but bound to whatever `this` refers to
within the anonymous function! Here, that happens to be the global object. There is no property called `baz` in the global object.

This line `typeof (f = foo.bar)();` could be rewritten as this

```js
f = foo.bar;
typeof f();
```

so the `this` in `foo.bar` refers to the global object.

----------------------------------------------

### Question

```js
var x = 1;
if (function f(){}) {
    x += typeof f;
}
x;
```

Answer: '1undefined'.

The dilemma is: is `function(){}` is a function expression or function declaration? (it is syntactically valid in both cases).
Functions are always truthy values in JS, so the above codes could be 

```js
var x = 1;
x += typeof f;
x;
```

`f` is not defined here, so `typeof f` yields the string `undefined`

---------------------------

### Question

```js
function f(){ return f; } 
new f() instanceof f; 
```

`new f()` instanceof `f` yields `false`. To understand why, it must first be known what `new f()` yields. The `new` operator creates a new object and calls the constructor function with this new object as its current context object. In other words, within the constructor, `this` points to the new object that is currently being created. After calling the constructor, the default semantics of the `new` operator is to yield said new object, even if the constructor returns some value. when the constructor returns an object, the new operator will yield the returned object. To illustrate this, consider the following code:

```js
var z = {a: 2}; 
function g() { return z; } 
var x = new g(); 
x === z; 
```

Here, `x` is actually equal to `z`, down to the identity! With this in mind, we know that `new f() === f`. The question now is what `f instanceof f` would yield. We know that `f` itself is a function, so it is an instance of the `Function` object. The fact that `f instanceof Function === true` proves that `f instanceof f` yields `false`.

----------------------------------------------------

Source:
- [quiz 1](http://kourge.net/node/130)
- [quiz 2](http://perfectionkills.com/javascript-quiz/)
- [interview question](https://www.toptal.com/javascript/interview-questions)
- [quiz answer](http://kourge.net/node/130)







