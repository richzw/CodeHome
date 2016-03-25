**Stream**

```js
var http = require('http');
var fs = require('fs');

var server = http.createServer(function (req, res) {
    var stream = fs.createReadStream(__dirname + '/kuaibo.txt');
    stream.pipe(res);
});
server.listen(8000);
```

```js
// simple HTTP proxy
var http = require('http');
var net = require('net');
var url = require('url');

function request(cReq, cRes) {
    var u = url.parse(cReq.url);
    var options = {
        hostname : u.hostname, 
        port     : u.port || 80,
        path     : u.path,       
        method     : cReq.method,
        headers     : cReq.headers
    };
    var pReq = http.request(options, function(pRes) {
        cRes.writeHead(pRes.statusCode, pRes.headers);
        pRes.pipe(cRes);
    }).on('error', function(e) {
        cRes.end();
    });
    cReq.pipe(pReq);
}

http.createServer().on('request', request).listen(8888, '0.0.0.0');
```

------------------------------------------------------

- **Check directory / file exist?**

```javascript
try {
		var protoPath = path.resolve(__dirname, './message');
		var stats = fs.statSync(protoPath);
} catch (e) {
		
}

```

---------------------------------------------------------

- **module.exports vs exports**

`module` is just a plain JavaScript object with an `exports` property. `exports` is a plain JavaScript variable that happens to be set to `module.exports`. At the end of your file, node.js will basically 'return' `module.exports` to the require function. A simplified way to view a JS file in Node could be this:

```javascript
var module = { exports: {} };
var exports = module.exports;

// your code

return module.exports;
```

If you set a property on `exports`, like `exports.a = 9;`, that will set `module.exports.a` as well because objects are passed around as references in JavaScript, which basically just means that if you set multiple variables to the same object, they are all the same object; so then exports and module.exports are the same object.
But if you set `exports` to something new, it will no longer be set to `module.exports`, so exports and `module.exports` are no longer the same object.

-----------------------------------

- 1.**What is Nodejs**

Nodejs is a platform for building fast, scalable network application. Its advantages over other server side languages is that it uses event-driven, non-blocking I/O model that makes it light-weight and efficient.

**Synchronous vs Asynchronous**

**Synchronous** execution usually refers to code executing in sequence. **Asynchronous** execution refers to execution that doesn't run in the sequence it appears in the code. In the following example, the synchronous operation causes the `alerts` to fire in sequence. In the async operation, while `alert(2)` appears to execute second, it doesn't.

```javascript
// Synchronous: 1,2,3
alert(1);
alert(2);
alert(3);

// Asynchronous: 1,3,2
alert(1);
setTimeout(() => alert(2), 0);
alert(3);
```

**Blocking vs Non-blocking**

**Blocking** refers to operations that block further execution until that operation finishes. **Non-blocking** refers to code that doesn't block execution. In the given example, localStorage is a blocking operation as it stalls execution to read. On the other hand, fetch is a non-blocking operation as it does not stall `alert(3`) from execution.

```javascript
// Blocking: 1,... 2
alert(1);
var value = localStorage.getItem('foo');
alert(2);

// Non-blocking: 1, 3,... 2
alert(1);
fetch('example.com').then(() => alert(2));
alert(3);
```

- 2. **Can you explain how Nodejs works**

It uses Google V8 Javascript engine to execute code. It contains built-in asynchronous I/O library for file, socket and HTTP communication. Node.js encapsulates libuv to handle asynchronous events.


- 3. **Is Nodejs really Single-Threaded**

Node.js operates on single-thread, but using non-blocking I/O calls allows it to support many concurrent connections. That means node doen't process the requests in parallel but all the back-end stuffs which actually takes lot of time run in parallel.

- 4. **Can you explain the Asynchronous approach in Nodejs**

Nodejs operats asynchronously using event loop and callback functions.An Event Loop is a functionality which handles and processes all your external events and just converts them to a callback function. It invokes all your event handlers at a proper time. So, that means while executing a single request, it does a lot of things in the back-end so that the current request or the coming request doesn't take much time.


- 5. **Can you explain what is Globals in Nodejs**

Global, Process and Buffer are combinedly termed as Globals.

  - Global : Its a global namespace object
  - Process : Its also a global object but it provides essential functionality to transform a synchronous function into a asynchronous callback.
  - Buffer : Raw data is stored in instances of the Buffer class.

- 6. **What is Callback in context of Node.js ?**

A callback is an asynchronous equivalent for a function which is being called when a given task is completed. Node.js makes heavy use of callbacks, all the API's are written such as way that it supports callbacks. The advantage of using callback is that it makes Node.js highly scalable i.e. processing high number of request without waiting for any function to complete. 

- 7. **What is Callback Hell and how to avoid it ?**

Callback hell means a heavily nested callbacks which make the code unreadable and difficult to maintain. To avoid callback hell one should use modularization, which means breaking the callbacks into independent functions. Another method to avoid callback hell is use to use Promises, which allows error propagation and chaining.

- 8. **What is Event Loop and Event Emitter ?**

Node.js supports concurrency with the help of events and callbacks even if it is single threaded application. Node thread keeps an event loop and whenever any task gets completed, that thread fires the corresponding event.

EventEmitter fires an event whenever any tasks gets completed, any error occurred, any new listener is added or any listener is removed. It provides properties like on and emit, where on is used to bind the function and emit is used to fire an event.
