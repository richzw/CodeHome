Question

Is it ever possible that (a ==1 && a== 2 && a==3) could evaluate to true, in JavaScript?

Answer

accepted
If you take advantage of how == works, you could simply create an object with a custom toString (or valueOf) function that changes what it returns each time it is used such that it satisfies all three conditions.

const a = {
  i: 1,
  toString: function () {
    return a.i++;
  }
}

if(a == 1 && a == 2 && a == 3) {
  console.log('Hello World!');
}


Source

https://stackoverflow.com/questions/48270127/can-a-1-a-2-a-3-ever-evaluate-to-true
