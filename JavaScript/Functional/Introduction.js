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

