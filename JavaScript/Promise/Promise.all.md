### Question

I can asynchronously resolve a bunch of promises with `Promise.all(array)`. However `.then()` will run only after all those promises have
been resolved. How I can perform actions as the promises get resolved?

For example, I want to load all paragraphs from an article asynchronously using `Promise.all()` - This way the network requests all fire
at once. If paragraph 1 is done loading, I want it to render to the page - but only if it is done loading before paragraph 2, then I want
paragraph 2 to load. If paragraph 3 is done loading and 2 is not, I want 3 to wait for 2 before rendering to the page. And so on.

I tried something like this but I don't know what to do next:

```javascript
var getStuff = function(number, time){
  return new Promise(function(resolve, reject){
    window.setTimeout(function(){resolve(`${number} - Done.`)}, time);
  });
};

Promise.all([ getStuff(1, 200),
              getStuff(2, 100),
              getStuff(3, 250),
              getStuff(4, 200),
              getStuff(5, 300),
              getStuff(6, 250),
              getStuff(7, 5000)])
.then(function(data){
  console.log(data);
});
```

### Answer

You can use `.all` for that with `.map`:

```javascript
Promise.all([ getStuff(1, 200),
            getStuff(2, 100),
            getStuff(3, 250),
            getStuff(4, 200),
            getStuff(5, 300),
            getStuff(6, 250),
            getStuff(7, 5000)]
.map(request => request.then(v => {
   console.log("Request done! Got," v); // or some action per request
   return v;
})).then(data => console.log(data));
```

You can boss this further with `.map` by using the fact you're using the same function for every request:

```javascript
Promise.all([[1, 200],
            [2, 100],
            [3, 250],
            [4, 200],
            [5, 300],
            [6, 250],
            [7, 5000]])
.map((a, b) => getStuff(a, b))
.map(request => request.then(v => {
   console.log("Request done! Got," v); // or some action per request
   return v;
})).then(data => console.log(data));
```

And further to:

```javascript
Promise.all([200, 100, 250, 200, 300, 250, 5000])
.map((a, i) => getStuff(a, i + 1))
.map(request => request.then(v => {
   console.log("Request done! Got," v); // or some action per request
   return v;
})).then(data => console.log(data));
```

Or with bluebird:

```javascript
const sideEffect = v => console.log("Got partial result", v));
const data = [200, 100, 250, 200, 300, 250, 5000];
Promise.map(data, (a, i) => getStuff(a, i + 1).tap(sideEffect))
       .then(data => console.log(data));
```
