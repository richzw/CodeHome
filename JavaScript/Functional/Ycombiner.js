// http://picasso250.github.io/2015/03/31/reinvent-y.html
(h =>
    (f => h ( v => f(f)(v) ))
    (f => h ( v => f(f)(v) ))
)

const Y = f =>
    (x => f(y => x(x)(y)))
    (x => f(y => x(x)(y)))


