JavaScript Promise
==============

Here is one old question from stack overflow

```javascript
function getY() {
  var y;
  $.get("/gety", function (jsonData) {
    y = jsonData.y;
  });
  return y;
}
 
var x = 5;
var y = getY();
console.log(x + y);
```

*Why doesn’t it work?*

In JavaScript we know doing asynchronicity through **callback**

```javascript
function getY(continueWith) {
  $.get("/gety", function (jsonData) {
    continueWith(jsonData.y);
  });
}
 
var x = 5;
getY(function (y) {
  console.log(x + y);
});
```

However, callback is not good. There are still several shortcoming

-	Doing things in sequence is hard

```javascript
$("#button").click(function () {
  promptUserForTwitterHandle(function (handle) {
    twitter.getTweetsFor(handle, function (tweets) {
      ui.show(tweets);
    });
  });
});
```

-	Doing things in parallel is harder

```javascript
var tweets, answers, checkins;
 
twitter.getTweetsFor("domenicdenicola", function (result) {
  tweets = result;
  somethingFinished();
});
stackOverflow.getAnswersFor("Domenic", function (result) {
  answers = result;
  somethingFinished();
});
fourSquare.getCheckinsBy("Domenic", function (result) {
  checkins = result;
  somethingFinished();
});
var finishedSoFar = 0;
 
function somethingFinished() {
  if (++finishedSoFar === 3) {
    ui.show(tweets, answers, checkins);
  }
}
```

-	Errors get lost easily

```javascript
function getTotalFileLengths(path, callback) {
  fs.readdir(path, function (err, fileNames) {
    var total = 0;
 
    var finishedSoFar = 0;
    function finished() {
      if (++finishedSoFar === fileNames.length) {
        callback(total);
      }
    }
 
    fileNames.forEach(function (fileName) {
      fs.readFile(fileName, function (err, file) {
        total += file.length;
        finished();
      });
    });
  });
}
```

To do it better, there are lots of libraries: *Async.js*, *async*, *atbar*…
[https://github.com/joyent/node/wiki/modules#wiki-async-flow](https://github.com/joyent/node/wiki/modules#wiki-async-flow)

IMO, the best of these are based on an abstraction called **Promise** 

	`Un-inverts the chain of responsibility, instead of calling a passed callback, return a promise`

```javascript
addWithCallback(a, b, function (result) {
  assert.equal(result, a + b);
});
 
var promise = addWithPromise(a, b);
 
promise.then(function (result) {
  assert.equal(result, a + b);
});
```

Why promise are awesome:

-	Cleaner method signature
-	Uniform return/error semantics

```javascript
$.ajax(url, settings)

settings.success(data, status, xhr)
settings.error(xhr, status, errorThrown)
settings.complete(xhr, status)
getAsPromise(url, [data], [dataType]).then(
  function onFulfilled(result) {
    var data = result.data;
    var status = result.status;
    var xhr = result.xhr;
  },
  function onBroken(error) {
    console.error("Couldn't get", error);
  }
);
```

-	Easy composition

```javascript
function getUser(userName, onSuccess, onError) {
  $.ajax("/user?" + userName, {
    success: onSuccess,
    error: onError
  });
}
```

can be changed to 

```javscript
function getUser(userName) {
  return getAsPromise("/user?" + userName);
}
```
example 2

```javscript
function getFirstName(userName, onSuccess, onError) {
  $.ajax("/user?" + userName, {
    success: function successProxy(data) {
      onSuccess(data.firstName);
    },
    error: onError
  });
}
```

can be changed to 

```javascript
function getFirstName(userName) {
  return getAsPromise("/user?" + userName)
           .get("firstName");
}
```

4.	Easy sequential/parallel join

Sequential

```javascript
$("#button").click(function () {
  promptUserForTwitterHandle(function (handle) {
    twitter.getTweetsFor(handle, function (tweets) {
      ui.show(tweets);
    });
  });
});
```

Can be changed to 

```javascript
$("#button").clickPromise()
  .then(promptUserForTwitterHandle)
  .then(twitter.getTweetsFor)
  .then(ui.show);
```

Parallel

```javascript
var tweets, answers, checkins;
 
twitter.getTweetsFor("domenicdenicola", function (result) {
  tweets = result;
  somethingFinished();
});
stackOverflow.getAnswersFor("Domenic", function (result) {
  answers = result;
  somethingFinished();
});
fourSquare.getCheckinsBy("Domenic", function (result) {
  checkins = result;
  somethingFinished();
});
```

can be changed to 

```javascript
Q.all([
  twitter.getTweetsFor("domenicdenicola"),
  stackOverflow.getAnswersFor("Domenic"),
  fourSquare.getCheckinsBy("Domenic")
]).then(function (results) {
  console.log(results[0], results[1], results[2]);
});
```

5.	Always async

```javascript
function getUser(userName, onSuccess, onError) {
  if (cache.has(userName)) {
    onSuccess(cache.get(userName));
  } else {
    $.ajax("/user?" + userName, {
      success: onSuccess,
      error: onError
    });
  }
}
console.log("1");
getUser("ddenicola", function (user) {
  console.log(user.firstName);
});
console.log("2");
```

输出结果不定，或者1, 2, Domenic. 亦或：1, Domenic, 2

但是改为promise之后，保证异步性质

```javascript
function getUser(userName) {
  if (cache.has(userName)) {
    return Q.ref(cache.get(userName));
  } else {
    return getWithPromise("/user?" + userName);
  }
}
console.log("1");
 
getUser("ddenicola").then(function (user) {
  console.log(user.firstName);
});
 
console.log("2");
// 1, 2, Domenic (every time)
```

6.	Exception-style error bubbling

```javascript
getUser("Domenic", function (err, user) {
  if (err) {
    ui.error(err);
  } else {
    getBestFriend(user, function (err, friend) {
      if (err) {
        ui.error(err);
      } else {
        ui.showBestFriend(friend);
      }
    });
  }
});
```
```javascript
getUser("Domenic")
  .then(getBestFriend, ui.error)
  .then(ui.showBestFriend, ui.error);
```
-------------------------------------------------------------------------------------------------------------------

```javascript
ui.startSpinner();
getUser("Domenic")
  .then(getBestFriend)
  .then(
    function (friend) {
      ui.showBestFriend(friend);
      ui.stopSpinner();
    },
    function (error) {
      ui.error(error);
      ui.stopSpinner();
    }
  );
```
```javascript
ui.startSpinner();
getUser("Domenic")
  .then(getBestFriend)
  .then(ui.showBestFriend, ui.error)
  .fin(ui.stopSpinner);
```
---------------------------------------------------------------------------------------------------------------------

```javascript
function getBestFriendAndDontGiveUp(user) {
  return getUser(user).then(
    getBestFriend,
    function (error) {
      if (error instanceof TemporaryNetworkError) {
        console.log("Retrying after error", error);
        return getBestFriendAndDontGiveUp(user);
      }
      throw error;
    });
}
```

*Fulfilling Promise*

Now we have: `setTimeout(doSomething, 1000);`

We want: `delay(1000).then(doSomething);`

```javascript
function delay(ms) {
  var deferred = Q.defer();
  setTimeout(deferred.resolve, ms);
  return deferred.promise;
}
```

breaking promise

```javascript
function getWithTimeout(url, ms) {
  var deferred = Q.defer();
 
  setTimeout(function () {
    deferred.reject(new Error("timed out"));
  }, ms);
 
  $.ajax(url, {
    success: deferred.resolve,
    error: deferred.reject
  });
 
  return deferred.promise;
}

function timeout(promise, ms) {
  var deferred = Q.defer();
  promise.then(deferred.resolve, deferred.reject);
 
  setTimeout(function () {
    deferred.reject(new Error("timed out"));
  }, ms);
 
  return deferred.promise;
}
 
function getWithTimeout(url, ms) {
  return timeout(getAsPromise(url), ms);
}
```

anything better? Sure, coroutines

`Coroutines are computer program components that generalize subroutines to allow multiple entry points 
for suspending and resuming execution at certain locations`
