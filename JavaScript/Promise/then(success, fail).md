
```javascript
some_promise_call()
.then(function(res) { logger.log(res) }, function(err) { logger.log(err) })
```

> It seems that the example is suggesting the following as the correctly way.

```javascript
some_promise_call()
.then(function(res) { logger.log(res) })
.catch(function(err) { logger.log(err) })
```

> What's the difference?

---------------------------------------------

![](http://i.stack.imgur.com/WAcpP.png)
![](http://i.stack.imgur.com/wX5mr.png)

To express it in synchronous code:

```javascript
// some_promise_call().then(logger.log, logger.log)
then: {
    try {
        var results = some_call();
    } catch(e) {
        logger.log(e);
        break then;
    } // else
        logger.log(results);
}
```

The second log (which is like the first argument to `.then()`) will only be executed in case that no exception happened. 
The labelled block and the break statement feel a bit odd, this is actually what python has `try-except-else` for (recommended reading!).

```python
// some_promise_call().then(logger.log).catch(logger.log)
try {
    var results = some_call();
    logger.log(results);
} catch(e) {
    logger.log(e);
}
```

The catch logger will also handle exceptions from the success logger call.

So much for the difference.

-----------------------------

> I don't quite understand its explanation as for the try and catch

The argument is that usually you want to catch errors in every step of the processing, and that you shouldn't use it in chains. 
The expectation is that you only have one final handler which handles all errors - while, when you use the "antipattern",
errors in some of the then-callbacks are not handled.

However, this pattern is actually very useful: When you want to handle errors that happened in exactly this step,
and you want to do something entirely different when no error happened - i.e. when the error is unrecoverable. 
Be aware that this is branching your control flow. Of course, this is sometimes desired.

What's wrong with this the following?

```javascript
some_promise_call()
.then(function(res) { logger.log(res) }, function(err) { logger.log(err) })
That you had to repeat your callback. You rather want

some_promise_call()
   .catch(function(e) {
       return e; // it's OK, we'll just log it
   })
   .done(function(res) {
       logger.log(res);
   });
```

You also might consider using `.finally()` for this.

