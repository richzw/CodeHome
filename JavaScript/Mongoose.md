Q: 

```js
var RoomSchema = new Schema({
  users: [{
    type: Schema.Types.ObjectId, ref: 'User',
  }]
});
```

users array will hold 2 users at one time.

My goal is to query,
if User A and User B exist in the array then simply console.log("Room Exist") else if both are not in the array then simply 
create a new room

--------------------------------------------

```js
Room.findOneAndUpdate(
    { "users": { "$all": [ userA, userB ] } },
    { "$addToSet": { "users": { "$each": [ userA, userB ] } } },
    { "upsert": true, "new": true, "passRawResult": true },
    function(err,newRoom,raw) {
        if ( raw.value.lastErrorObject.updatedExisting == true ) {
            // Then the room was already found
        } else {
            // newRoom has the updated object data
        }
    })
)
```

So th basic case is that by using .findOneAndUpdate() this is now one operation. By looking at the "rawResult" from the option there,
then you can tell if a new document was created or not.

The $addToSet makes sure that nothing new really gets added on match. But you could use $setOnInsert instead.

-----------------------------------------

Q: calculate average from date ranges

```js
{
    "_id" : ObjectId("56ad2e080fa76101bdd17573"),
    "date" : ISODate("2016-01-30T21:40:00Z"),
    "response_times" : [
        10,
        22,
        21,
        37
    ]
}
{
    "_id" : ObjectId("56ad2c9d0fa76101bdd17572"),
    "date" : ISODate("2016-01-30T21:35:00Z"),
    "response_times" : [
        27,
        32
    ]
}
```

You can use the aggregation framework for this:

```js
db.so.aggregate( 
    [ { $unwind : "$response_times" }, 
      { $group: 
          { _id:"$date", 
            average: { $avg : "$response_times" } } } 
    ] )
```

