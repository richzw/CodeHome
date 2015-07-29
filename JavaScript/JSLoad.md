
[AMD, CommonJS, Require.js](http://stackoverflow.com/questions/16521471/relation-between-commonjs-amd-and-requirejs)
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

On the contrary, `Require.JS` implements AMD, which is designed to suit the browser environment(source). Apparently AMD started as an offspin of CommonJS Transport format and evolved into its own module definition API. Hence the similiarities between the two. The new thing in AMD is the `define()`
-function that allows the module to declare its dependencies before being loaded. For example the definition could be:

```javascript
define('module/id/string', ['module', 'dependency', 'array'], 
function(module, factory function) {
  return ModuleContents;  
});
```

一个用来进行模块定义的 define 方法以及一个用来处理依赖项加载的 require 方法

So CommonJS and AMD are JavaScript module definition APIs that have different implementations, but both come from the same origins.

- **AMD** is more suited for the browser, because it supports asynchronous loading of module dependencies.
- **Require.JS** is an implementation of AMD, while at the same time trying to keep the spirit of CommonJS (mainly in the module identifiers).

To confuse you even more, RequireJS, while being an AMD implementation, offers a CommonJS wrapper so CommonJS modules can almost directly be imported into use with RequireJS.

```javascript
define(function(require, exports, module) {
  var someModule = require('someModule'); // in the vein of node    
  exports.doSomethingElse = function() { return someModule.doSomething() + "bar"; };
});
```

-------------------------------------

- 对于依赖的模块，AMD 是提前执行，CMD 是延迟执行。
- CMD 推崇依赖就近，AMD 推崇依赖前置。
- AMD 的 API 默认是一个当多个用，CMD 的 API 严格区分，推崇职责单一

AMD 采取了一种浏览器优先的方式来开发，选择了异步行为与简化的向后兼容性，但它完全没有文件 I/O 的概念。它支持对象、函数、构造器、字符串、JSON 以及其它许多类型的模块，运行在浏览器本地环境之中。它有着难以想象的灵活性。

CommonJS 则采用了服务器优先的策略，采取同步行为、没有 John Hann 所说的那种全局的累赘、并且着眼于适应未来的场景（在服务器上）。这么说的意思是，CJS 支持未包裹的模块，感觉上更接近 ES.next/Harmony 规范，把你从 AMD 要求的 define() 包裹函数中解放了出来。

[Ref](https://github.com/seajs/seajs/issues/588)

[Ref1](http://justineo.github.io/singles/writing-modular-js/)

