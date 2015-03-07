Promise 
---------

JavaScript is functional programming language???
-	function are first-class values

The feature of functional programming
-	immutable data
-	preference for recursion over looping
-	algebraic type system
-	avoidance of side effect
-	programming with value, everything is value. This is core

Nodejs asynchronous through callback.

Actually, **promise** provide a compelling alternative to raw callback when dealing with asynchronous codes.

What is a _promise_?

    A promise is an abstraction for asynchronous programming. 
    It’s an object that proxies for the return value or the exception thrown by a function 
    that has to do some asynchronous processing

```javascript
var promise = doSomethingAync()
promise.then(onFulfilled, onRejected)
```

Here is one example

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

optimize
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








