
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

---------------------------------------------------

**Class Free OOP**

-------------------------------------

[Ref](https://dannyfritz.wordpress.com/2014/10/11/class-free-object-oriented-programming/)

A Duck, an Alligator, and a Goat

Let’s say we want to create a Duck class in this paradigm.

- Inherit from the base Object and create an Animal class.
- Inherit from the Animal class and create a Duck class.
- Define swim, walk, talk, and fly methods on Duck.

Easy right? But wait a second. New requirements have come in and you need to define Alligator and Goat now.

- Inherit from Animal and create an Alligator class.
- Define walk, swim, and talk on Alligator.
- Inherit from Animal and create a Goat class.
- Define walk and talk on Goat.

All done! Okay, time to refactor and clean up. walk, swim, fly, and talk are not specific to those animals are they? We should probably move them to a shared class to be more DRY. We should move the methods to Animal so they can be shared among the animals and written once. Cool, now walk, talk, fly, and swim are written only once!

But wait, Alligator shouldn’t be able to fly! We need an additional class between Animal and the animals to account for this. Let’s create a FlyingAnimal inheriting from Animal so we can account for the Duck that flies. Oh, and Goat doesn’t swim like Duck and Alligator. So we need to create a SwimmingAnimal to account for that and assign Alligator and Duck to it, but not Goat. But wait, Duck can’t inherit from FlyingAnimal in addition to SwimmingAnimal and WalkingAnimal!


```javascript
var withAnimal = {
  name: 'name',
  word: 'word',
  talk: function () {
    console.log(this.name + ' says ' + this.word);
  }
};

var withFlying = {
  fly: function () {
    console.log('flap flap');
  }
};

var withSwimming = {
  swim: function () {
    console.log('splish splash');
  }
};

var withWalking = {
  walk: function () {
    console.log('stomp stomp');
  }
};

function extend (target, source) {
  Object.keys(source).forEach(function (key) {
    if (typeof target[key] !== 'undefined') {
      return;
    }
    target[key] = source[key];
  });
}

function newAlligator () {
  var alligator = {
    name: 'alligator',
    word: 'grrr'
  };
  extend(alligator, withAnimal);
  extend(alligator, withWalking);
  extend(alligator, withSwimming);
  return alligator;
}

function newDuck () {
  var duck = {
    name: 'duck',
    word: 'quack'
  };
  extend(duck, withAnimal);
  extend(duck, withWalking);
  extend(duck, withFlying);
  extend(duck, withSwimming);
  return duck;
}

function newGoat () {
  var goat = {
    name: 'goat',
    word: 'baa'
  };
  extend(goat, withAnimal);
  extend(goat, withWalking);
  return goat;
}

var alligator = newAlligator();
alligator.talk();
alligator.swim();
alligator.walk();

var duck = newDuck();
duck.talk();
duck.fly();
duck.walk();

var goat = newGoat();
goat.talk();
goat.walk();

```
