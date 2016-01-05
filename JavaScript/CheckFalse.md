
- `varName === void 0`

This will detect whether varName is `undefined`.

`void` is an operator which receives an argument (you can use whatever instead of 0), and returns `undefined`.

- `varName === undefined`

This should detect whether varName is `undefined`.

However, be aware the global `undefined` could have been overwritten (before ES5) or shadowed with another value. 
Therefore I prefer void, which is also shorter.

- `varName == null`

This will detect whether varName is `undefined` or is `null`.

- `!varName`

This will detect whether varName is `falsy` (`undefined`, `null`, `0`, `empty string`, `NaN`, `false`).
