// http://picasso250.github.io/2015/03/31/reinvent-y.html
(h =>
    (f => h ( v => f(f)(v) ))
    (f => h ( v => f(f)(v) ))
)

const Y = f =>
    (x => f(y => x(x)(y)))
    (x => f(y => x(x)(y)))

// sampel codes
const factorial = Y(
    f => n => n == 0 ? 1 : n * f(n - 1)
)

const reverse = Y(
   rev => ([x, ...xs]) =>
       x === undefined ?
       [] :
       [...rev(xs), x]
)

const tailReverse = seq => Y(
    rev => ([x, ...xs]) => ret =>
        x === undefined ?
        ret :
        rev(xs)([x, ...ret])
)(seq)([])

const gcd = (a, b) => Y(
    _gcd => a => b =>
        b == 0 ? a : _gcd(b)(a % b)
)(a)(b)

// http://jimliu.net/2015/10/15/functional-reverse-in-es6/
