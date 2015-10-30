

------------------------------------------------------

- **Check directory / file exist?**

```javascript
try {
			var protoPath = path.resolve(__dirname, './message');
			var stats = fs.statSync(protoPath);
		} catch (e) {
		
		}

```

---------------------------------------------------------

- **module.exports vs exports**

`module` is just a plain JavaScript object with an `exports` property. `exports` is a plain JavaScript variable that happens to be set to `module.exports`. At the end of your file, node.js will basically 'return' `module.exports` to the require function. A simplified way to view a JS file in Node could be this:

```javascript
var module = { exports: {} };
var exports = module.exports;

// your code

return module.exports;
```

If you set a property on `exports`, like `exports.a = 9;`, that will set `module.exports.a` as well because objects are passed around as references in JavaScript, which basically just means that if you set multiple variables to the same object, they are all the same object; so then exports and module.exports are the same object.
But if you set `exports` to something new, it will no longer be set to `module.exports`, so exports and `module.exports` are no longer the same object.
