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
      }
    ]
)
```

