### prototype vs __proto__


[Javascript Object treasure map](http://i.stack.imgur.com/KFzI3.png)

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
