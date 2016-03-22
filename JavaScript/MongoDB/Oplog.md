
[Query Oplog node.js](https://www.compose.io/articles/the-mongodb-oplog-and-node-js/)

```js
var MongoDB = require('mongodb');

// get the oplog URL
oplogurl = 'mongodb://<user>:<password>@candidate.11.mongolayer.com:10240,candidate.0.mongolayer.com:10240/local?authSource=wiktory'

// open db connection 
MongoDB.MongoClient.connect(oplogurl, function(err, db) {  

    // get oplog collection
    db.collection("oplog.rs", function(err, oplog) {

        // find the highest timestamp
        var ts = new MongoDB.Timestamp(0, Math.floor(new Date().getTime() / 1000)),
            query = { "$gt": ts };

        // create a tailable cursor and set it to await data
        cursor = oplog.find({ ts: query }, {
            tailable: true,
            awaitdata: true,
            oplogReplay: true,
            numberOfRetries: -1
        });

        // wrap that cursor in a Node Stream
        stream = cursor.stream();

        // log to console when data arrives
        stream.on('data', function(oplogdoc) {
            console.log(oplogdoc);
        });

    });
});

```

Under Mongoose

```js
var mongoose = require('mongoose');
var MongoDB = require('mongodb');
mongoose.connect('mongodb://localhost/local');  

var conn = mongoose.connection;
conn.on('error', console.error.bind(console, 'connection error:'));
conn.once('open', function callback () {

    var oplog = conn.db.collection('oplog.rs');

    // find the highest timestamp
    var ts = new MongoDB.Timestamp(0, Math.floor(new Date().getTime() / 1000)),
        query = { "$gt": ts };

    // create a tailable cursor and loop each oplog entry
    oplog.find({ ts: query }, { tailable: true }).each(function(err, entry) {
        if (err) { /* handle error */ } 
        else {
            // log new oplog entry                                                                                                                                           
            console.log(JSON.stringify(entry));
        }
    })
});
```
