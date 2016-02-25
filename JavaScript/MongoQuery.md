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



