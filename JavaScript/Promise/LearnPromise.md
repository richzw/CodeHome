
---------

[Traffic Light Improvement in Promise](http://blog.csdn.net/aimingoo/article/details/45014325)


```javascript
function turn(color, duration) {
  return new Promise(function(resolve, reject) {
    traffic.className = color
    setTimeout(resolve, duration)
  })
}

//执行！
void function run() {
    turn('green', 1000)
    .then(turn.bind(null, 'yellow', 400))
    .then(turn.bind(null, 'red', 1000))
    .then(run)
}()

```

```javascript
// 点亮指定颜色的灯，颜色值由turn.bind()通过this传入
function turn() {
    traffic.className = this;
}

// 抽象的执行器，每step为[wait, andRun]
function runner(step){
    return new Promise(function(resolve) {
        setTimeout(resolve, step[0]);
    }).then(step[1])
}

// 获得迭代器中的iterator.next()的成员，并使之resolved
//  - 通过picker.bind()将iterator绑定到this
function picker(item) {
    return (item = this.next()).done ? Promise.reject(item) : Promise.resolve(item.value[1]);
}

// 可以提前就绪(ready)的数据
var promisedData = [
    [0,     turn.bind('green')],  // step1
    [5000,  turn.bind('yellow')], // step2
    [2000,  turn.bind('red')],    // ...
    [5000,  main]
];

function main() {
    var iteratorPromise = Promise.resolve(promisedData.entries());
	iteratorPromise.then(function(iterator) {
        var getPromisedItem = picker.bind(iterator);
        return function loop() {
	        return getPromisedItem().then(runner).then(loop);
        }()
    })
}

main()
```

```javascript
function turn() {
    traffic.className = this;
}

function runner(step){
    return new Promise(function(resolve) {
        setTimeout(resolve, step[0]);
    }).then(step[1])
}

function loop(promise, next, runner) {
    return promise.then(next).then(function(it) {
        return !it.done && loop(runner(it.value[1]), next, runner)
    })
}

void function() {
    Promise.resolve([
        [0,     turn.bind('green')],
        [5000,  turn.bind('yellow')],
        [2000,  turn.bind('red')],
        [5000,  arguments.callee]
    ].entries()
    ).then(function(iterator) {
        return loop(Promise.resolve('begin'), iterator.next.bind(iterator), runner)
    });
}()

```

```javascript
function timeout(ms) {
	return new Promise(function(next) { setTimeout(next, ms) })
}
function turn(color) {
	return Promise.resolve(traffic.className = color);
}
function runner(data){
	// 请试想这里为什么不直接用data[1](data[0]) ?
    return Promise.resolve(data[0]).then(data[1]);
}
function picker(item) {
    return (item = this.next()).done ? Promise.reject(item) : Promise.resolve(item.value[1]);
}

var promisedData = [
	[0,     timeout],  // step1
	['green', turn],   // step2
	[2000,  timeout],  // ...
	['yellow', turn],
 	[5000,  timeout],
 	['red', turn],
 	[2000,  timeout],
 	[undefined, main]
];

function main() {
    // 典型的基于iterator的递归写法，不再依赖一层resolve
    return function(iterator) {
        var promised = picker.bind(iterator);
        return function next() {
            return promised().then(runner).then(next);
        }()
    }(promisedData.entries());
}

main()

```
