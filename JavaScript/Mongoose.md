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

------------------------------

Q:

 Prevent empty element is added into subdocument array.

```js 
db.collection.update(
    { },
    { "$pull": { "tradename": { "element": { "$exists": false } } } },
    { "multi": true }
)
```

----------------------------------------

Q:

convert 

```js
{
     "user1":["l1","l2","l3","l4","l5"]
     "user2":["l2","l3",l4","l7"]
     "user3":["l7,"l5"]
}
```

So I want to convert this collection into reverse index form

```js
{
      "l1":[user1]
      "l2":[user1,user2]
      "l3":[user1,user2]
      "l4":[user1,user2]
      "l5":[user1,user3]
      "l7":[user2,user3]
}
```

```js
db.users.aggregate([{$unwind:'$l'},{$group:{_id:'$l',users:{$push:'$name'}}}])
```

----------------------------------------------

Q: $lookup in the embeded document.

```js
{
     "name": "Joe Soap",
     "gender": "male",
     "employee_no: 123245678,
     "jobs": [
         {
             "name": "Defy washing machine repair",
             "spares": '569f6d002e16e55f2f8958d9',
         },
         {
             "name": "Samsung fridge regas",
             "spares": '569f6d002e16e55f2f8958e4',
         }
     ]
}
```

with `$lookup`

```js
db.doc.aggregate([
  {$unwind: '$jobs'}, 
  {$lookup: 
    {from: 'spares', 
     localField: 'jobs.spares', 
     foreignField: '_id', 
     as: 'sp'}}, 
  {$unwind: '$sp'}, 
  {$group: 
    {'_id': '$_id', 
    jobs: {$push: '$sp'}}}
]);
```
