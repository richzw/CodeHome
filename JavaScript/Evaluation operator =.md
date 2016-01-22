
```js
var foo = {n: 1};
var bar = foo;
foo.x = foo = {n: 2}; // explain it???
```

the left hand side of an assignment expression is evaluated first, even though the operator has right-to-left precedence. 
Thus the expression `foo.x = foo = {n: 2}` which is the same as `foo.x = (foo = {n: 2})` is evaluated like this:

- Evaluate the left-hand expression `foo.x` to get a reference, which is where the value of the right-hand expression will be assigned to.

- Evaluate the right-hand expression, to to get the value that will be assigned. The right-hand side is another assignment expression,
so it gets evaluated the same way:

  - Evaluate `foo` to determine where to assign to.
  - Evaluate the expression `{n:2}`, which creates an object, to determine the value to assign.
  - Assign `{n:2}` to `foo`, and return `{n:2}`.

- Assign the value that the expression on the right-side evaluated to `({n:2})`, to the reference that `foo.x` resolved to in step 1 
(before foo was assigned a new value). Which is also the same as `bar.x`, because of the assignment `bar = foo` on the line before.

When this is done, the original object, that `bar` is still a reference to, will have an `x` property that references the second object
created. `foo` is also a reference to that second object, so `foo === bar.x.`


