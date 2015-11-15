"Smart" but naïve way
-----------

```javascript
uniqueArray = a.filter(function(item, pos) {
    return a.indexOf(item) == pos;
})
```

Basically, we iterate over the array and, for each element, check if the first position of this element in the array is equal
to the current position. Obviously, these two positions are different for duplicate elements.

Using the 3rd ("this array") parameter of the filter callback we can avoid a closure of the array variable:

```javascript
uniqueArray = a.filter(function(item, pos, self) {
    return self.indexOf(item) == pos;
})
```

Although concise, this algorithm is not particularly efficient for large arrays (quadratic time).

Hashtables to the rescue
-------------------------------

```javascript
function uniq(a) {
    var seen = {};
    return a.filter(function(item) {
        return seen.hasOwnProperty(item) ? false : (seen[item] = true);
    });
}
```

This is how it's usually done. The idea is to place each element in a hashtable and then check for its presence instantly.
This gives us linear time, but has at least two drawbacks:

- since hash keys can only be strings in Javascript, this code doesn't distinguish numbers and "numeric strings". That is, 
`uniq([1,"1"])` will return just `[1]`
- for the same reason, all objects will be considered equal: `uniq([{foo:1},{foo:2}])` will return just `[{foo:1}]`.

That said, if your arrays contain only primitives and you don't care about types (e.g. it's always numbers), 
this solution is optimal.

The best from two worlds
-------------------------------

An universal solution combines both approaches: it uses hash lookups for primitives and linear search for objects.

```javascript
function uniq(a) {
    var prims = {"boolean":{}, "number":{}, "string":{}}, objs = [];

    return a.filter(function(item) {
        var type = typeof item;
        if(type in prims)
            return prims[type].hasOwnProperty(item) ? false : (prims[type][item] = true);
        else
            return objs.indexOf(item) >= 0 ? false : objs.push(item);
    });
}
```

sort | uniq
--------------------------

Another option is to sort the array first, and then remove each element equal to the preceding one:

```javascript
function uniq(a) {
    return a.sort().filter(function(item, pos, ary) {
        return !pos || item != ary[pos - 1];
    })
}
```

Again, this doesn't work with objects (because all objects are equal for sort), unless a special compare function can be
provided. Additionally, this method silently changes the original array as a side effect - not good!
However, if your input is already sorted, this is the way to go (just remove sort from the above).

Unique by...
----------------------

Sometimes it's desired to uniquify a list based on some criteria other than just equality, for example, 
to filter out objects that are different, but share some property. This can be done elegantly by passing a callback. 
This "key" callback is applied to each element, and elements with equal "keys" are removed. Since key is expected to
return a primitive, hash table will work fine here:

```javascript
function uniqBy(a, key) {
    var seen = {};
    return a.filter(function(item) {
        var k = key(item);
        return seen.hasOwnProperty(k) ? false : (seen[k] = true);
    })
}
```

A particularly useful key() is JSON.stringify which will remove objects that are physically different, but "look" the same:

```javascript
a = [[1,2,3], [4,5,6], [1,2,3]]
b = uniqBy(a, JSON.stringify)
console.log(b) // [[1,2,3], [4,5,6]]
```

Performance
---------------------------

Function calls are expensive in Javascript, therefore the above solutions, as concise as they are, are not particularly
efficient. For maximal performance, replace filter with a loop and get rid of other function calls:

```javascript
function uniq_fast(a) {
    var seen = {};
    var out = [];
    var len = a.length;
    var j = 0;
    for(var i = 0; i < len; i++) {
         var item = a[i];
         if(seen[item] !== 1) {
               seen[item] = 1;
               out[j++] = item;
         }
    }
    return out;
}
```

This chunk of ugly code does the same as the snippet #3 above, but an order of magnitude faster:

ES6
-------------------

ES6 provides the `Set` object, which makes things a whole lot easier:

```javascript
function uniq(a) {
  var seen = new Set();
  return a.filter(function(x) {
    return !seen.has(x) && seen.add(x);
  })
}
```

Or

```javascript
var uniq = [ ...new Set(names) ];
```
