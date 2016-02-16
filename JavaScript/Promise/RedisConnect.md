
```js
let _connectResolve, _connectReject, onConnected = new Promise((resolve, reject) => {
    _connectResolve = resolve;
    _connectReject = reject;
 }), redis = require("redis"),
 client = redis.createClient();

client.on('connect', _connectResolve);

// usage example:
onConnected.then(() => {
  client.setAsync("foo_rand000000000000", "some fantastic value").then(redis.print);
    client.getAsync("foo_rand000000000000").then(redis.print);
});
```

if your worry is, you have to wait for client to connect before you get/ set stuff, you can chain all your calls to onConnected promise. e.g:

```js
app.get('/redis', (req, res) => {
  onConnected
    .then(() => client.setAsync("foo_rand000000000000", "some fantastic value"))
    .then(() => res.end());
});
```

