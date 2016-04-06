// for loop
const two_steps = step1 => step2 => param => step2(step1(param))

const loop_on_array = arr => body => i =>
    i < arr.length ?
    two_steps (body) (_ => loop_on_array(arr)(body)(i + 1)) (arr[i]) :
    undefined

// test code
loop_on_array ([1, 2, 3, 4, 5]) (item => console.log(item)) (0)

// map function
const map = f => arr =>
    arr.length === 0 ?
    [] :
    [f(arr[0])].concat(map(f)(arr.slice(1)))

const map = f => ([x, ...xs]) =>
    x === undefined ?
    [] :
    [f(x), ...map(f)(xs)]
    
// test codes
const double = arr =>
    map(x => x * 2)(arr)

double([1, 2, 3, 4, 5])

// sum example
const sum = accumulator => ([x, ...xs]) =>
    x === undefined ?
    accumulator :
    sum (x + accumulator) (xs)

sum (0) ([1, 2, 3, 4, 5])

const _sum = accumulator => ([x, ...xs]) =>
    x === undefined ?
    accumulator :
    _sum (x + accumulator) (xs)

const sum = xs => _sum (0) (xs)

// reduce
const foldr = f => accumulator => ([x, ...xs]) =>
    x === undefined ?
    accumulator :
    f (x) (foldr(f)(accumulator)(xs))
    
const map = f => foldr (x => acc => [f(x), ...acc]) ([])
const sum = foldr (x => acc => x + acc) (0)

map (x => x * 2) ([1, 2, 3, 4, 5]) 
sum ([1, 2, 3, 4, 5])    

// return to for loop
const loop_on_array = f => foldr(x => _ => f(x)) (undefined)
loop_on_array (x => console.log(x)) ([1, 2, 3, 4, 5])

const foldl = f => accumulator => ([x, ...xs]) =>
    x === undefined ?
    accumulator :
    foldl (f) (f(accumulator)(x)) (xs)
    
const loop_on_array = f => foldl(_ => x => f(x)) (undefined)
loop_on_array (x => console.log(x)) ([1, 2, 3, 4, 5])
    
// http://jimliu.net/2015/10/21/real-functional-programming-in-javascript-1/


