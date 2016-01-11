
With `bluebird` you can use `Promise.promisifyAll` (and `Promise.promisify`) to add Promise ready methods to any object.

```javascript
var Promise = require('bluebird');
// Somewhere around here, the following line is called
Promise.promisifyAll(connection);

exports.getUsersAsync = function () {
    return connection.connectAsync()
        .then(function () {
            return connection.queryAsync('SELECT * FROM Users')
        });
};
```

And use like this:

```
getUsersAsync().then(console.log);
```

or

```javascript
// Spread because MySQL queries actually return two resulting arguments, 
// which Bluebird resolves as an array.
getUsersAsync().spread(function(rows, fields) {
    // Do whatever you want with either rows or fields.
});
```

Adding disposers

`Bluebird` supports a lot of features, one of them is disposers, it allows you to safely dispose of a connection after it ended with
the help of Promise.using and Promise.prototype.disposer. Here's an example from my app:

```javascript
function getConnection(host, user, password, port) {
    // connection was already promisified at this point

    // The object literal syntax is ES6, it's the equivalent of
    // {host: host, user: user, ... }
    var connection = mysql.createConnection({host, user, password, port});
    return connection.connectAsync()
        // connect callback doesn't have arguments. return connection.
        .return(connection) 
        .disposer(function(connection, promise) { 
            //Disposer is used when Promise.using is finished.
            connection.end();
        });
}
```

Then use it like this:

```javascript
exports.getUsersAsync = function () {
    return Promise.using(getConnection(), function (connection) {
            return connection.queryAsync('SELECT * FROM Users')
        });
};
```

