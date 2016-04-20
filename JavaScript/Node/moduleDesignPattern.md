
Source: [Design Patterns for Node.js Modules](http://bites.goodeggs.com/posts/export-this/)

1. Exports a NameSpace
----------------

Example 1: `fs` core module

```js
var fs = exports;
fs.readFile = function(path, options, callback_) {
  // ...
};
fs.ReadStream = ReadStream;

function ReadStream(path, options) {
  // ...
}
ReadStream.prototype.open = function() {
  // ...
}
```

Example 2: 

```js
module.exports = {
  version: '1.0',

  doSomething: function() {
    //...
  }
}
```

2. Exports a Function
------------------

Example: `Express.js`

```js
exports = module.exports = createApplication;

function createApplication () {
  ...
}
```

When exporting a function, it is good practice to _name the function_ so that it will show up in stack traces.

3. Exports a Higher Order Function
---------------------------

Example: Connection middleware

```js
var qs = require('qs')
  , parse = require('../utils').parseUrl;

module.exports = function query(options){
  return function query(req, res, next){
    if (!req.query) {
      req.query = ~req.url.indexOf('?')
        ? qs.parse(parse(req).query, options)
        : {};
    }

    next();
  };
};
```

4. Exports a Constructor
-----------------------

```js
function Person(name) {
  this.name = name;
}

Person.prototype.greet = function() {
  return "Hi, I'm " + this.name;
};

module.exports = Person;
```

5. Exports a Singleton
--------------------

Example: `Mongoose`

```js
function Mongoose() {
  //...
}

module.exports = exports = new Mongoose();
```

6. Extends a Global Object
-----------------------

Example: `Should.js`

```js
var should = function(obj) {
  return new Assertion(util.isWrapperType(obj) ? obj.valueOf(): obj);
};

//...

exports = module.exports = should;

//...

Object.defineProperty(Object.prototype, 'should', {
  set: function(){},
  get: function(){
    return should(this);
  },
  configurable: true
});
```

`Should.js` extends Object with a non-enumerable property should to provide a clean syntax for writing unit test asserts.

```js
require('should');

var user = {
    name: 'Jane'
};

user.name.should.equal('Jane');
```

7. Applies a Monkey Patch
---------------------------

```js
var model = Mongoose.prototype.model;
var modelWithUnderScoreCollectionName = function(name, schema, collection, skipInit) {
  collection = collection || _(name).chain().underscore().pluralize().value();
  model.call(this, name, schema, collection, skipInit);
};
Mongoose.prototype.model = modelWithUnderScoreCollectionName;
```
