
How does require find a module?
-------------------

Searches:

- **Core modules**: Built in modules
- **node_modules**: works up path until it matches or hits the root
- **NODE_PATH**: includes globally installed packages
- $HOME/.node_modules
- $HOME/.node-libraries

How does require work?
-------------------

`moduler.require` which wraps `Module._load()`, `_load` steps:

- Check **Module._cache** for a cached copy
- Create a new Module instance if cache miss
- Save it to the cache
- Call load with the given filename
- Compile the file contents
- If there was an error delete from cache
- Return **module.exports**

How does compile work?
-------------------

- Create a standalone require function that calls `module.require`
- Attaches other helper methods to require
- wrap the loaded JS codes in a function that provides the require from step1, module, and variables to the module scope
- run the function

```js
(function(exports, require, module, __filename, __dirname) {
      // code injected here
});
```

`module.exports` vs `exports`
----------------------

- `module.exports` is the **real deal**. `exports` is just `module.exports`'s little helper. Your module returns `module.exports` to the caller ultimately, not `exports`. All exports does is collect properties and attach them to `module.exports`

Good example:

```js
module.exports.age = 68;
exports.name = 'Lemmy Kilmister';
```

However, bad example

```js
module.exports = 'LOL';
module.exports.age = 68;
exports.name = 'Lemmy Kilmister';
```

- Do NOT overwrite `module.exports` with anything in your module

Circular dependencies in module?
--------------------------

```js
//a.js:

console.log('a starting');
exports.done = false;
const b = require('./b.js');
console.log('in a, b.done = %j', b.done);
exports.done = true;
console.log('a done');

//b.js:

console.log('b starting');
exports.done = false;
const a = require('./a.js');
console.log('in b, a.done = %j', a.done);
exports.done = true;
console.log('b done');

//main.js:

console.log('main starting');
const a = require('./a.js');
const b = require('./b.js');
console.log('in main, a.done=%j, b.done=%j', a.done, b.done);
```

When `main.js` loads `a.js`, then `a.js` in turn loads `b.js`. At that point, `b.js` tries to load `a.js`. _In order to prevent an infinite loop_, an **unfinished copy** of the `a.js` exports object is returned to the `b.js` module. `b.js` then finishes loading, and its exports object is provided to the `a.js` module. 

Solve the circle dependencies
-----------------------

Issue:

```js
// Module A
var B = require('./B');

var A = module.exports = {
    init : function(val) {
        id = val;
        bInstance = new B();
        return this;
    },
}

// Module B
var A = require('./A');

var B = module.exports = function(){
    return {
        stuff : function() {
            console.log('I got the id: ', A.getId());
        }
    };
};
```

**Solution 1**: delay invocation of dependency until runtime

```js
// Module A
var A = module.exports = {
    init : function(val) {
        id = val;
        bInstance = new require('./B')();
        return this;
    },
}
```

**Solution 2**: dependency injection

```js
// Module A
var B = require('./B');

var A = module.exports = {
    init : function(val) {
        id = val;
        bInstance = new B(this);
        return this;
    },
}

// Module B
var B = module.exports = function(val){
    var dependency = val;
    return {
        stuff : function() {
            console.log('I got the id: ', dependency.getId());
        }
    };
};
```
