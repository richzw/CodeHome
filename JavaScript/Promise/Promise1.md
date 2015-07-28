Promise 
---------

JavaScript is functional programming language???
-	function are first-class values

However, the feature of _functional programming_
-	immutable data
-	preference for recursion over looping
-	algebraic type system
-	avoidance of side effect
-	programming with **value**, everything is value. This is core

Nodejs asynchronous through callback.

Oh, my God, [callback hell](http://callbackhell.com/)

Actually, **promise** provide a compelling alternative to raw callback when dealing with asynchronous codes.

What is a _promise_?

    A promise is an abstraction for asynchronous programming. 
    It’s an object that proxies for the return value or the exception thrown by a function 
    that has to do some asynchronous processing

```javascript
var promise = doSomethingAync()
promise.then(onFulfilled, onRejected)
```

Here is one example, first begin from callback

Get files mtime
**callback version**
```javascript
var async = require('async'),     
  fs    = require('fs');  

var paths = ['file1.txt', 'file2.txt', 'file3.txt'];  
async.map(paths, fs.stat, function(error, results) {   
    // use the results 
  // get file time
});
```

Get the file size
```javascript
var paths = ['file1.txt', 'file2.txt', 'file3.txt'];  
async.map(paths, fs.stat, function(error, results) {   
// use the results 
});  
fs.stat(paths[0], function(error, stat) {   
// use stat.size 

});
```

```javascript
var paths = ['file1.txt', 'file2.txt', 'file3.txt'],     
  file1 = paths.shift();  

fs.stat(file1, function(error, stat) {   
   // use stat.size   
   async.map(paths, fs.stat, function(error, results) {     
       results.unshift(stat);     
       // use the results   
   }); 

}); 
```

```javascript
var paths = ['file1.txt', 'file2.txt', 'file3.txt'],     
   file1 = paths.shift();  

async.parallel([   
   function(callback) {     
        fs.stat(file1, function(error, stat) {      
            // use stat.size       
            callback(error, stat);     
        });   
    },   function(callback) {     
        async.map(paths, fs.stat, callback);   
    } 
], function(error, results) {   
    var stats = [results[0]].concat(results[1]);   
    // use the stats
});
```

mission complete?

_convert to promise version_

```javascript
var fs_stat = promisify(fs.stat);

var paths = ['file1.txt', 'file2.txt', 'file3.txt'],
    statsPromises = list(paths.map(fs_stat));

statsPromises[0].then(function(stat) {
  // use stat.size
});

statsPromises.then(function(stats) {
  // use the stats
});
```

function promisify
```javascript
// promisify :: (a -> (Error -> b -> ()) -> ()) -> (a -> Promise b)
var promisify = function(fn, receiver) {
  return function() {
    var slice   = Array.prototype.slice,
        args    = slice.call(arguments, 0, fn.length - 1),
        promise = new Promise();

    args.push(function() {
      var results = slice.call(arguments),
          error   = results.shift();

      if (error) promise.reject(error);
      else promise.resolve.apply(promise, results);
    });

    fn.apply(receiver, args);
    return promise;
  };
};

// list :: [Promise a] -> Promise [a]
var list = function(promises) {
  var listPromise = new Promise();
  for (var k in listPromise) promises[k] = listPromise[k];

  var results = [], done = 0;

  promises.forEach(function(promise, i) {
    promise.then(function(result) {
      results[i] = result;
      done += 1;
      if (done === promises.length) promises.resolve(results);
    }, function(error) {
      promises.reject(error);
    });
  });

  if (promises.length === 0) promises.resolve(results);
  return promises;
};
```






