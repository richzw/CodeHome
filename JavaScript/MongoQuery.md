Q:

```js
{
  _id : ObjectId("sdfsdf"),
  result : [1, 3, 5, 7, 9]
},
{
  _id : ObjectId("asdref"),
  result : [2, 4, 6, 8, 10]
}
```

I want to get the sum of those result arrays, but not a total sum, 
instead a new array corresponding to the sum of the original arrays on an element basis, i.e.

`result : [3, 7, 11, 15, 19]`

A:

```js
.aggregate(
    [
      {
        "$unwind" :  { path: "$result", includeArrayIndex: "arrayIndex" }
      },
      {
        "$group": {
          "_id": "$arrayIndex",
          "results" : { "$sum" : "$result"}
          }
      },
      { 
        $sort: { "_id": 1}
      },
      {
        "$group":{
          "_id": null,
          "results":{"$push":"$results"}
          } 
      },
      {
        "$project": {"_id":0,"results":1}
      }
    ]
)
```

---------------------------------------

Q:

```js
{
  "_id": "56c58adf4f40",
  "data1": "test1",
   "data2": "test2"

}

//I need output to be like data2 = data1 + data2 for all records.

{
  "_id": "56c58adf4f40",
  "data1": "test1",
   "data2": "test1 test2"

}
```

A:

```js
var cursor = db.collection.aggregate([
        {
            "$project": {
                "data1": 1,
                "data2": { $concat: [ "$data1", " ", "$data2" ] }
            }
        }
    ]),
    updateCollUsingAgg = function(doc){
        db.collection.update(
            { "_id": doc._id },
            { "$set": { "data2": doc.data2 } }
        )
    }

cursor.forEach(updateCollUsingAgg);

var cursor = db.collection.find(),
    updateCollUsingFind = function(doc){
        db.collection.update(
            { "_id": doc._id },
            { "$set": { "data2": doc.data1+" "+doc.data2 } }
        )
    };
cursor.forEach(updateCollUsingFind);
```

---------------------------------------------------------------------

Q: remove duplicat document from collection

A: 
```js
var bulk = db.testkdd.initializeOrderedBulkOp(),
    count = 0;

// List "all" fields that make a document "unique" in the `_id`
// I am only listing some for example purposes to follow
db.testkdd.aggregate([
    { "$group": {
        "_id": {
           "duration" : "$duration",
          "protocol_type": "$protocol_type", 
          "service": "$service",
          "flag": "$flag"
        },
        "ids": { "$push": "$_id" },
        "count": { "$sum": 1 }
    }},
    { "$match": { "count": { "$gt": 1 } } }
],{ "allowDiskUse": true}).forEach(function(doc) {
    doc.ids.shift();     // remove first match
    bulk.find({ "_id": { "$in": doc.ids } }).remove();  // removes all $in list
    count++;

    // Execute 1 in 1000 and re-init
    if ( count % 1000 == 0 ) {
       bulk.execute();
       bulk = db.testkdd.initializeOrderedBulkOp();
    }
});

if ( count % 1000 != 0 ) 
    bulk.execute();
```

----------------------------------------------------------------------------

Q: When I get the above project with the USER role, I need to have the following representation, without the `OTHER` file :

```
{
  "_id": ObjectId("..."),
  "title": "MySuperProject",
  "files": [
    {
      "title":"My skiing day !",
      "right":[{
        "role":"USER",
        "access":["read"]
      }]
    },
    {
      "title":"My little dog, so cute !",
      "right":[{
        "role":"OTHER",
        "access":["read"]
      }]
    }
  ]
}
```

A:

```
db.t.aggregate([
  {
    $match: {
      "title": projectTitle
    }
  },
  {
    $redact: {
      $cond: [{
        $eq: [role, {
          $ifNull: ["$role", role]
        }]
      }, "$$DESCEND", "$$PRUNE"]
    }
  },
  {
    $redact: {
      $cond: [{
        $gt: [{
          $size: {
            $ifNull: ["$right", [1]]
          }
        }, 0]
      }, "$$DESCEND", "$$PRUNE"]
    }
  },
])
```

----------------------------

```js
  { 
            "_id" : "9aa072e4-b706-47e6-9607-1a39e904a05a", 
            "customerId" : "2164289-4", 
            "channelStatuses" : [
                {
                    "channel": "FOO",
                    "status" : "done"
                }, 
                {
                    "channel": "BAR",
                    "status" : "error"
                }
            ], 
            "channel" : "BAR", 
    }
```

```js
{ "$group": {
        "_id": {
            "customerId" : "$customerId", 
            "channel" : "$channel", 
            "status": {
                "$arrayElemAt": [
                    { "$map": {
                        "input": { "$filter": {
                            "input": "$chanelStatuses",
                            "as": "el", 
                            "cond": { "$eq": [ "$$el.channel", "$channel" ] }
                        }},
                        "as": "el",
                        "in": "$$el.status"
                    }},
                    0
                ]
            }
        },
        "count": { "$sum": 1 }
    }}
```

----------------------------------------

Q: Update large collection

A:

> `node --max-old-space-size=4096 server.js`

> Currently, by default v8 has a memory limit of 512MB on 32-bit systems, and 1.4GB on 64-bit systems. The limit can be raised by setting --max_old_space_size to a maximum of ~1024 (~1 GB) (32-bit) and ~4096 (~4GB) (64-bit), but it is recommended that you split your single process into several workers if you are hitting memory limits

Or 

You can use the `async.eachLimit` method of the `async` library to limit the number of concurrent save operations.

For example, to limit the saves to no more than 5 outstanding at a time:

```js
MyModel.find().exec(function(err, data){
   if (err) {
      return console.log(err);
   }
   async.eachLimit(data, 5, function(doc, callback){
      doc.Field = doc.Field + 1;
      doc.save(function(err) {
        if (err) {
          console.error('ERROR!');
        }
        callback(err);
      });
   });
});
```

-----------------------------------------------------

Q: Pull data from array nested array

```js
{
    "_id" : "FfEj5chmviLdqWh52",
    "favorites" : [ 
        [ 
            5719, 
            "2016-03-21T17:46:01.441Z", 
            "a"
        ]
    ]
}
```

A:

```js
users.update(
  { "favorites": { "$elemMatch": { "$elemMatch": { "$eq": 5719 }  } } },
  { "$pull": { "favorites.$": 5719 } }
)
```



