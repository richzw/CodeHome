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

function add(num1, num2){
  let r1, r2, m;
  r1 = (''+num1).split('.')[1].length;
  r2 = (''+num2).split('.')[1].length;

  m = Math.pow(10,Math.max(r1,r2));
  return (num1 * m + num2 * m) / m;
}
console.log(add(0.1,0.2));   //0.3
console.log(add(0.15,0.2256)); //0.3756

