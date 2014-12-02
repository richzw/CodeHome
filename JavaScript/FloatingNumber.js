> 0.1 + 0.2 == 0.3
false

> 0.1 + 0.2
0.30000000000000004

//why?
//http://stackoverflow.com/questions/588004/is-floating-point-math-broken

fix it
----------------------------------------------------------
x = 0.2;
y = 0.3;
equal = (Math.abs(x - y) < 0.000001)

(0.1 + 0.2).toPrecision(10) == 0.3
> true

(0.1 + 0.2).toFixed(10) == 0.3
> true
