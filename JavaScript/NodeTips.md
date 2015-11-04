

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


