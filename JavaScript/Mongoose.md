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

