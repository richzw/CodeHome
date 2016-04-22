
**Q: I want to run the same action whether my Promise resolved successfully or not.**
------------------------------------------

**A**:

You can implement the `finally` method yourself like this:

```js
Promise.prototype.finally = function(cb) {
    const res = () => this
    const fin = () => Promise.resolve(cb()).then(res)
    return this.then(fin, fin);
};
```

or more extensively, with passing resolution information to the callback:

```js
Promise.prototype.finally = function(cb) {
    const res = () => this
    return this.then(value =>
        Promise.resolve(cb({state:"fulfilled", value})).then(res)
    , reason =>
        Promise.resolve(cb({state:"rejected", reason})).then(res)
    );
};
```
Both ensure that the original resolution is sustained (when there is no exception in the callback) and that promises are awaited.

**Source**:

[promise settle](http://stackoverflow.com/questions/32362057/es6-promise-settled-callback)
