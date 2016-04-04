// reverse string or array 
function recursiveReverse(seq) {
    return seq.length > 1 ?
        recursiveReverse(seq.slice(1)).concat(seq.slice(0, 1)) : seq;
}

// tail recursive version
function tailReverse(seq) {
    return (function rev(seq, ret) {
        return seq.length > 0 ?
            rev(seq.slice(1), seq.slice(0, 1).concat(ret)) : ret;
    })(seq, seq.slice(0, 0));
}

// ES6 destructuring assignment and spread operator
function pmReverse([x, ...xs]) {
    return typeof x === "undefined" ? [] : pmReverse(xs).concat([x]);
}

// tail recursive under ES6
function pmTailReverse(list) {
    return (function rev([x, ...xs], ret) {
        return typeof x === "undefined" ? ret : rev(xs, [x].concat(ret));
    })(list, []);
}

// http://jimliu.net/2015/10/14/curry-function-in-es6/
// curry 
var curry = fn => (...left) => (...right) => fn(...left, ...right)
var concat = (...args) => args.join('')

var hehe = curry(concat)('hehe', 'haha')
console.log(hehe('heihei')) // hehehahaheihei

var curryR = fn => (...right) => (...left) => fn(...left, ...right)

Function.prototype.curry = function(...left) {
  return curry(this)(...left)
}

Function.prototype.curryR = function(...right) {
  return curryR(this)(...right)
}

var append = concat.curry('hehe')
var prepend = concat.curryR('hehe')

console.log(append('1')) // hehe1
console.log(prepend('1')) // 1hehe

var saySomethingTo = (word, name, end) => concat(word, ', ', name, end)

var sayHelloTo = saySomethingTo.curry('Hello').curryR('!!!')
console.log(sayHelloTo('Jim')) 
