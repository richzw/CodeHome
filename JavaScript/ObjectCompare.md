### Question

For 

```js
var a = new Object();
var b = new Object();
```

and after comparing, I have got those results:

```js
var a = new Object();
var b = new Object();
console.log(a == b); //false
console.log(a > b); //false
console.log(b > a); //false
console.log(a >= b); //true
console.log(b >= a); //true
```

### Answer

Object references compared with `==` or `!=` (or `===` or `!==`) are compared based on whether they refer to the **same object**.
If so, they're equal; if not, they're not equal.

But the relational comparison operators (`>`, `<`, `>=`, and `<=`) don't compare the references, they coerce their operands to something
they can compare: `Numbers` or `strings`.

In the case of `new Object()`, that coercion ends up creating a string: `"[object Object]"`. And of course, `"[object Object]" >= "[object Object]"`
is true because they're equal.

So in effect, what you're actually doing is:

```js
console.log(a == b);                 //false
console.log(String(a) > String(b));  //false
console.log(String(b) > String(a));  //false
console.log(String(a) >= String(b)); //true
console.log(String(b) >= String(a)); //true
```

...but note that other object types coerce differently, because objects can choose how they coerce in this situation (where the spec
prefers a number over a string) by implementing/overriding valueOf. For instance, Date objects coerce to a number when you apply a 
relational operator to them if the other operand can also coerce to number. So you can reliably use `dt1 > dt2` to see if dt1 represents
a date/time after dt2 — but you can't use `dt1 == dt2` to check if dt1 and dt2 (two separate Date objects) have the same date/time
in them, because == will check to see if they're the same object instead. Which leads us to this bit of amusement:

```js
var dt1 = new Date(2016, 5, 23);
var dt2 = new Date(2016, 5, 23);
console.log(dt1 < dt2);  // false
console.log(dt1 > dt2);  // false
console.log(dt1 == dt2); // false!
```

### Source

http://stackoverflow.com/questions/37998267/comparing-a-new-object-with-another-new-object-in-javascript
