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
