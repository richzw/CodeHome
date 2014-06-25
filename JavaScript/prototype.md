## prototype vs __proto__

`__proto__` is the actual object taht is used in the lookup chain to resolve methods.
`prototype` is the object that is used to build `__proto__` when you create an object with `new`

[Javascript Object treasure map](http://i.stack.imgur.com/KFzI3.png)
![Alt text](http://i.stack.imgur.com/KFzI3.png)

  ```javascript
  Object.O1 = '';
  Object.prototype.Op1='';
  
  Function.F1 = '';
  Function.prototype.Fp1 = '';
  
  Cat = function(){};
  Cat.C1 = '';
  Cat.prototype.Cp1 = '';
  
  mycat = new Cat();
  o = {};
  ```
