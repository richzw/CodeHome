
[AMD, CommonJS (CMD?), Require.js](http://stackoverflow.com/questions/16521471/relation-between-commonjs-amd-and-requirejs)
============================

**RequireJS** implements the **AMD** API (source).

**CommonJS** is a way of defining modules with the help of an exports object, that defines the module contents.
Simply put a CommonJS implementation might work like this

```javascript
// someModule.js
exports.doSomething = function() { return "foo"; };

//otherModule.js
var someModule = require('someModule'); // in the vein of node    
exports.doSomethingElse = function() { return someModule.doSomething() + "bar"; };
```

Basically CommonJS specifies that you need to have a the `require()` function to fetch dependencies, the `exports` variable to export module contents and some module identifier (that describes the location of the module in question in relation to this module) that is used to require the dependencies(source). CommonJS has various implementations, for example Node.js that you mentioned.

**CommonJS** was not particularly designed with browsers in mind so, it doesn't fit to the browser environment very well (I really have no source for this, it just says so everywhere, for example the RequireJS site.). Apparently this has something to do with asynchronous loading etc.

On the contrary, RequireJS implements AMD, which is designed to suit the browser environment(source). Apparently AMD started as an offspin of CommonJS Transport format and evolved into its own module definition API. Hence the similiarities between the two. The new thing in AMD is the `define()`
-function that allows the module to declare its dependencies before being loaded. For example the definition could be:

```javascript
define('module/id/string', ['module', 'dependency', 'array'], 
function(module, factory function) {
  return ModuleContents;  
});
```

So CommonJS and AMD are JavaScript module definition APIs that have different implementations, but both come from the same origins.

- **AMD** is more suited for the browser, because it supports asynchronous loading of module dependencies.
- **RequireJS** is an implementation of AMD, while at the same time trying to keep the spirit of CommonJS (mainly in the module identifiers).

To confuse you even more, RequireJS, while being an AMD implementation, offers a CommonJS wrapper so CommonJS modules can almost directly be imported into use with RequireJS.

```javascript
define(function(require, exports, module) {
  var someModule = require('someModule'); // in the vein of node    
  exports.doSomethingElse = function() { return someModule.doSomething() + "bar"; };
});
```

- 对于依赖的模块，AMD 是提前执行，CMD 是延迟执行。
- CMD 推崇依赖就近，AMD 推崇依赖前置。
- AMD 的 API 默认是一个当多个用，CMD 的 API 严格区分，推崇职责单一

[Ref](https://github.com/seajs/seajs/issues/588)

