### Question

Following the question Extending String.prototype performance I am really intrigued, because just adding "use strict" to a 
`String.prototype` method improved performance 10 times. The explanation by bergi is short and does not explain it to me. 
Why there is such a dramatic difference between two almost identical methods, that only differ in "use strict" at the top? 
Can you explain in more detail and with the theory behind this?

```js
String.prototype.count = function(char) {
  var n = 0;
  for (var i = 0; i < this.length; i++)
    if (this[i] == char) n++;
  return n;
};

String.prototype.count_strict = function(char) {
  "use strict";
  var n = 0;
  for (var i = 0; i < this.length; i++)
    if (this[i] == char) n++;
  return n;
};
// Here is how I measued speed, using Node.js 6.1.0

var STR = '0110101110010110100111010011101010101111110001010110010101011101101010101010111111000';
var REP = 1e4;

console.time('proto');
for (var i = 0; i < REP; i++) STR.count('1');
console.timeEnd('proto');

console.time('proto-strict');
for (var i = 0; i < REP; i++) STR.count_strict('1');

console.timeEnd('proto-strict');
```

### Answer

	
In strict mode, the this context is not forced to be an object. If you call a function on a non-object, this will just be that 
non-object.

In contrast, in non-strict mode, the this context is always first wrapped in an object if it's not already an object. For example, 
`(42).toString()` first wraps 42 in a Number object and then calls Number.prototype.toString with the Number object as this context. 
In strict mode, the this context is left untouched and just calls Number.prototype.toString with 42 as this context.

```js
(function() {
  console.log(typeof this);
}).call(42); // 'object'

(function() {
  'use strict';
  console.log(typeof this);
}).call(42); // 'number'
```

In your case, the non-strict mode version spends a lot of time wrapping and unwrapping primitive strings into String object wrappers
and back. The strict mode version on the other hand directly works on the primitive string, which improves performance
