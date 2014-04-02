var a = undefined;
var a = null;

if (!undefined) 
    console.log('undefined is false');
// undefined is false

if (!null) 
    console.log('null is false');
// null is false
undefined == null
// true

Number(null)
// 0
5 + null
// 5

Number(undefined)
// NaN
5 + undefined
// NaN

//null是一个表示"无"的对象，转为数值时为0；undefined是一个表示"无"的原始值，转为数值时为NaN。
//null表示"没有对象"，即该处不应该有值
//（1） 作为函数的参数，表示该函数的参数不是对象。
//（2） 作为对象原型链的终点。
Object.getPrototypeOf(Object.prototype)
// null

//undefined表示"缺少值"，就是此处应该有一个值，但是还没有定义
//（1）变量被声明了，但没有赋值时，就等于undefined。
//（2) 调用函数时，应该提供的参数没有提供，该参数等于undefined。
//（3）对象没有赋值的属性，该属性的值为undefined。
//（4）函数没有返回值时，默认返回undefined。
var i;
i // undefined

function f(x){console.log(x)}
f() // undefined

var  o = new Object();
o.p // undefined

var x = f();
x // undefined

