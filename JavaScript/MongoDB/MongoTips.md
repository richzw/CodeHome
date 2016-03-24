Source: http://devblog.me/wtf-mongo


1. Keys order in a hash object
---------------

**The gotcha**: the order of keys matters in MongoDB, i.e. `{ a: 1, b: 2 }` does not match `{ b: 2, a: 1 }`.

**Why does it happen:** MongoDB uses a binary data format called `BSON`. In `BSON`, the order of keys always matters. 
Notice, in JSON an object is an _unordered set_ of `key/value` pairs.

What about JavaScript? ECMA-262 left it as `'undefined'`. In some browsers (usually old ones) the order of pairs is not preserved meaning
they can be anything. Thankfully most modern browsers' JavaScript engines preserve the order (sometimes even in arrays), so we can actually control it from node.js code.

---------------------------

2. null and undefined
------------

MongoDB brings it to the next level. The BSON spec defines `undefined` as **"deprecated"**.

Node.js node-native-driver for MongoDB doesn't implement it at all.

```
> db.thing.find({a: null})
{ "_id" : ObjectId("56f39131cdb91d93acb5198c"), "a" : null, "b" : 1 }
{ "_id" : ObjectId("56f39138cdb91d93acb5198d"), "a" : undefined, "b" : 1 }
{ "_id" : ObjectId("56f39336cdb91d93acb5198e"), "b" : 1 }
```

----------------------

3. limit
---------

```js
function getItems (N) {
  if (N < 0) N = -N;
  if (N > 50 || !N) // check if N is falsy ("no limit")
    N = 50;
  return db.items.find({}).sort({ year: 1 }).limit(N);
}
```

-------------------

4. Mongo sorting
--------

For data

```js
{
  _id: 'A',
  locations: [5, 1, 3]
}
{
  _id: 'B',
  locations: [2, 4, 9]
}
{
  _id: 'C',
  locations: [1]
}
```

with codes `collection.find().sort({locations: 1})`

```
_id:       A C B A B A B
locations: 1 1 2 3 4 5 9
```

--------------------------



