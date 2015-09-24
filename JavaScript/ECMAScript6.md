
Given the new toolset provided by ES6 lots of programmers, aiming at code simplification, expressiveness, efficiency, 
skim through their old code and make tweaks (some pointless, some successful) to achieve their goals. 
Whilst trying not to loose too much time on such labors and just make non intrusive and self contained changes, 
what are the best practices?

-----------------------------------

- tail calls

replace `while`

```javascript
	function repeat(func) {
		while (func() !== undefined) {
		}
	}
```

with `tail calls`

```javascript
	function repeat(func) {
		if (func() !== undefined) {
			return repeat(func);
		}
	}
```

- Ellipsis `...`

replace 

```javascript
function curry(func) {
	var slice = Array.prototype.slice, args = slice.call(arguments, 1);
	return function () {
		return func.apply(null, args.concat(slice.call(arguments, 0)));
	}
}
```

with 

```javascript
function curry(func, ...first) {
	return function(...second) {
		return func(...first, ...second);  
	}
}
```

- module: `export`, `import`

```javascript
// --file.js--
function getJSON(url, callback) {
  let xhr = new XMLHttpRequest();
  xhr.onload = function () { 
    callback(this.responseText) 
  };
  xhr.open("GET", url, true);
  xhr.send();
}

export function getUsefulContents(url, callback) {
  getJSON(url, data => callback(JSON.parse(data)));
}

// --main.js--
import { getUsefulContents } from "file.js";
getUsefulContents("http://www.example.com", data => {
  doSomethingUseful(data);
});
```

- new data structure, `Set`, `WeakSet`, `Map`, `WeakMap`

http://stackoverflow.com/questions/29413222/what-are-the-actual-uses-of-es6-weakmap
http://stackoverflow.com/questions/32710432/es6-set-weakset-map-and-weakmap
http://fitzgeraldnick.com/weblog/53/


- `let` keyword
  
	let `blocking scope` vs var `function scope`

- Destructuring

```javascript
	let {that, other} = another_obj;
	let that = another_obj.that, other = another_obj.other;
```	
	
