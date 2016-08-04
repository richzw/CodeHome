
### Difference

- `setImmediate()` queues its callbacks in the event queue after I/O and timer callbacks.
- `process.nextTick()` queues its callbacks before I/O and timer callbacks.

`setImmediate` is similiar to `setInterval/setTimeOut` in that it has a `cancelImmediate()` in the same way as `canceInterval/cancelTimeout`,
but it lacks a time as a second argument. 

Code Test

```js
var emitter = new require('events').EventEmitter();

setImmediate(function() {
    console.log("IMMEDIATE");
});

process.nextTick(function() {
    console.log("NEXTTICK");
});
```

### process.nextTick() Usage

- **Interleaving execution of a CPU intensive task with other events**

Let's say we have a task `compute()` which needs to run almost continuously, and does some CPU intensive calculations. If we wanted to 
also handle other events, like serving HTTP requests in the same Node process, we can use `process.nextTick()` to interleave the execution
of `compute()` with the processing of requests this way:

```js
var http = require('http');

function compute() {
    // performs complicated calculations continuously
    // ...
    process.nextTick(compute);
}

http.createServer(function(req, res) {
     res.writeHead(200, {'Content-Type': 'text/plain'});
     res.end('Hello World');
}).listen(5000, '127.0.0.1');

compute();
```

- **Keeping callbacks truly asynchronous**

When you are writing a function that takes a callback, you should always ensure that this callback is fired asynchronously. Let's look 
at an example which violates this convention:

```js
function asyncFake(data, callback) {        
    if(data === 'foo') callback(true);
    else callback(false);
}

asyncFake('bar', function(result) {
    // this callback is actually called synchronously!
});
```

We can correct `asyncFake()` to be always asynchronous this way:

```js
function asyncReal(data, callback) {
    process.nextTick(function() {
        callback(data === 'foo');       
    });
}
```

- **When emitting events**

Let's say you are writing a library that reads from a source and emits events that contains the chunks that are read. Such a library 
might look like this:

```js
var EventEmitter = require('events').EventEmitter;

function StreamLibrary(resourceName) { 
    this.emit('start');

    // read from the file, and for every chunk read, do:        
    this.emit('data', chunkRead);       
}
StreamLibrary.prototype.__proto__ = EventEmitter.prototype;   // inherit from EventEmitter
```

we can use `process.nextTick()` to defer the emit till the listener has had the chance to listen for the event.

```js
function StreamLibrary(resourceName) {      
    var self = this;

    process.nextTick(function() {
        self.emit('start');
    });

    // read from the file, and for every chunk read, do:        
    this.emit('data', chunkRead);       
}
```


### Source

http://becausejavascript.com/node-js-process-nexttick-vs-setimmediate/
https://howtonode.org/understanding-process-next-tick


