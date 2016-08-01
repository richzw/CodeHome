
### Question

Can someone please explain what is happening in it step by step?

```js
> function dis() { return this }
undefined
> five = dis.call(5)
Number {[[PrimitiveValue]]: 5}
> five.wtf = 'potato'
"potato"
> five.wtf
"potato"
> five * 5
25
> five.wtf
"potato"
> five++
5
> five.wtf
undefined
> five.wtf = 'potato?'
"potato?"
> five.wtf
undefined
> five
6
```


### Answer

Before stepping through the behaviour, its important to clarify a few things:

- `Number value` and `Number object` (`a = 3` vs `a = new Number(3)`) are very different. One is a primitive, the other is an object.
You cannot assign attributes to primitives, but you can to objects.

- Coercion between the two is implicit. For example:

```js
(new Number(3) === 3)  // returns false
(new Number(3) == 3)   // returns true, as the '==' operator coerces
(+new Number(3) === 3) // returns true, as the '+' operator coerces
```

- Every Expression has a return value. When the REPL reads and executes an expression, this is what it displays. The return values often
don't mean what you think and imply things that just aren't true.

Ok, here we go.

The pledge.

```js
> function dis() { return this }
undefined
> five = dis.call(5)
[Number: 5]
```

Define a function `dis` and call it with `5`. This will execute the function with `5` as the context (this). Here it is coerced from a
Number value to a Number object. It is very important to note that were we in `strict mode` this would not have happened.

```js
> five.wtf = 'potato'
'potato'
> five.wtf
'potato'
```

Now we set the attribute five.wtf to 'potato', and with five as an object, sure enough it accepts the Simple Assignment.

> five * 5
25
> five.wtf
'potato'
With five as an object, I ensure it can still perform simple arithmetic operations. It can. Do its attributes still stick? Yes.

The turn.

```js
> five++
5
> five.wtf
undefined
```

Now we check `five++`. The trick with postfix increment is that the entire expression will evaluate against the original value and then 
increment the value. It looks like five is still five, but really the expression evaluated to five, then set five to 6.

Not only did five get set to 6, but it was coerced back into a Number value, and all attributes are lost. Since primitives cannot hold
attributes, five.wtf is undefined.

```js
> five.wtf = 'potato?'
'potato?'
> five.wtf
undefined
```

I again attempt to reassign an attribute wtf to five. The return value implies it sticks, but it in fact does not because five is a
Number value, not a Number object. The expression evaluates to 'potato?', but when we check we see it was not assigned.

The prestige.

```js
> five
6
```

Ever since the postfix increment, five has been `6`.

