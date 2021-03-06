//http://macr.ae/article/memoization-javascript.html

/**
 * A memoize function to cache return values where possible.
 *
 * @author Callum Macrae (@callumacrae)
 * @license Public domain.
 *
 * @param fn The function to memoize.
 * @param sort If true, arguments will be sorted. Useful for functions where
 *             the order of arguments don't matter.
 */
function memoize(fn, sort) {
    var cache = {};

    return function () {
        var args = Array.prototype.slice.call(arguments);

        if (sort) {
            args.sort();
        }

        if (cache[JSON.stringify(args)] !== undefined) {
            return cache[JSON.stringify(args)];
        }

        var result = fn.apply(this, args);
        cache[JSON.stringify(args)] = result;
        return result;
    };
}


// example...
var fibonacciFromCache = memoize(fibonacci);

console.time('Memoized function call');
for (var i = 0; i < 3; i++) {
    fibonacciFromCache(40);
}
console.timeEnd('Memoized function call');


// simple version

var memoize = function(func){
    var cache = {};
    return function(){
        var key = Array.prototype.slice.call(arguments).toString();
        return key in cache ? cache[key] : (cache[key] = func.apply(this,arguments));
    }
}
fibonacci = memoize(fibonacci);

var memoize = function(func){
    const cache = {};
    return (...args) => {
        const key = [...args].toString();
        return key in cache ? cache[key] : (cache[key] = func(...args));
    }
}
fibonacci = memoize(fibonacci);

var gcd = memoize(function(a,b){
    var t;
    if (a < b) t=b, b=a, a=t;
    while(b != 0) t=b, b = a%b, a=t;
    return a;
})
gcd(27,183); //=> 3
