### Question

```javascript
> 0.1 + 0.2 == 0.3
false

> 0.1 + 0.2
0.30000000000000004
```

why? //http://stackoverflow.com/questions/588004/is-floating-point-math-broken

### Solution

```javascript
x = 0.2;
y = 0.3;
equal = (Math.abs(x - y) < 0.000001)

(0.1 + 0.2).toPrecision(10) == 0.3
> true

(0.1 + 0.2).toFixed(10) == 0.3
> true

function add(num1, num2){
  let r1, r2, m;
  r1 = (''+num1).split('.')[1].length;
  r2 = (''+num2).split('.')[1].length;

  m = Math.pow(10,Math.max(r1,r2));
  return (num1 * m + num2 * m) / m;
}
console.log(add(0.1,0.2));   //0.3
console.log(add(0.15,0.2256)); //0.3756
```

### Question

Does the following `for loop` stop:

```javascript
for  (var i=0; 1/i > 0; i++) {
}
```

### Answer

The loop won't stop in a correctly-implemented JavaScript engine. (_The engine's host environment might eventually terminate it because it's endless, but that's another thing._)

Here's why:

- Initially, when `i` is `0`, the condition `1/i > 0` is `true` because in JavaScript, `1/0` is `Infinity`, and `Infinity > 0` is `true`.
- After that, `i` will be incremented and continue to grow as a positive integer value for a long time (a further `9,007,199,254,740,990` iterations). In all of those cases, `1/i` will remain `> 0` (although the values for `1/i` get really small toward the end!) and so the loop continues up to and including the loop where `i` reaches the value `Number.MAX_SAFE_INTEGER`.
- `Number.MAX_SAFE_INTEGER (9,007,199,254,740,991)` is the highest positive integer value that an IEEE-754 double-precision binary number (the kind JavaScript uses) can accurately represent. Once we go past this point, we start losing precision even at the whole number (integer) scale.
- After the loop where `i` is `Number.MAX_SAFE_INTEGER`, `i++` takes us to an inaccurate number. If you printed out the value of `i` at that point, it would say `9,007,199,254,740,992`, but it isn't quite `9,007,199,254,740,992`. Double precision numbers famously can't represent all numbers (`0.1 + 0.2 == 0.3` is `false`, for instance), but we're used to thinking (erroneously) that it only affects the fractional part. It doesn't, and this is the point at which it starts affecting the whole-number part. `1/i` is still `> 0` so the loop continues.
- From that point forward, `i++` doesn't change the value of `i` anymore; adding `1` to it doesn't change the bit pattern held for the number at all. Adding a higher number like `10` to it would, but adding `1` to it doesn't. So we've reached steady-state: `i` never changes, and the loop never terminates.

Here are the various relevant calculations:

```javascript
var i = 0;
console.log(i, 1/i, 1/i > 0); // 0, Infinity, true
i++;
console.log(i, 1/i, 1/i > 0); // 1, 1, true
// ...eventually i is incremented all the way to Number.MAX_SAFE_INTEGER
i = Number.MAX_SAFE_INTEGER;
console.log(i, 1/i, 1/i > 0); // 9007199254740991 1.1102230246251568e-16, true
i++;
console.log(i, 1/i, 1/i > 0); // 9007199254740992 1.1102230246251565e-16, true
i++;
console.log(i, 1/i, 1/i > 0); // 9007199254740992 1.1102230246251565e-16, true (no change)
console.log(i == i + 1);      // true
```



