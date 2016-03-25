How to handle the exception in nodejs
======================

[http://shapeshed.com/uncaught-exceptions-in-node/](http://shapeshed.com/uncaught-exceptions-in-node/)

- You application shouldn't have uncaught exceptions. This is clearly insane.
- You should let your application crash, find uncaught exceptions and fix them. This is clearly insane.
- You should swallow errors silently. This is what lots of people do and it is bad.
- You should let your application crash, log errors and restart your process with something like upstart, forever or monit. This is pragmatic.
- You should start using domains to handle errors. Clearly the way to go, although this is an experimental feature of Node.

- try catch
---

```js
var http = require('http');

http.createServer(function(req, res) {
  try {
    handler(req, res);
  } catch(e) {
    console.log('\r\n', e, '\r\n', e.stack);
    try {
      res.end(e.stack);
    } catch(e) { }
  }
}).listen(8080, '127.0.0.1');

console.log('Server running at http://127.0.0.1:8080/');

var handler = function (req, res) {
  //Error Popuped
  var name = req.params.name;

  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('Hello ' + name);
};
```

- node-forever 
---

    [sudo] npm install forever
    
    $ forever start simple-server.js
    
- shell
---

 /etc/init.d/ourjs

```shell
WEB_DIR='/var/www/ourjs'
WEB_APP='svr/ourjs.js'

#location of node you want to use
NODE_EXE=/root/local/bin/node

while true; do
    {
        $NODE_EXE $WEB_DIR/$WEB_APP config.magazine.js
        echo "Stopped unexpected, restarting \r\n\r\n"
    } 2>> $WEB_DIR/error.log
    sleep 1
done
```
