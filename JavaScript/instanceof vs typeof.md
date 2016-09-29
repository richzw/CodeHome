
### Difference

**typeof**, you get a string representation of the object type.

**instanceof**, you are comparing the type, specifically if the property of a _constructor_ is in the **objects prototype chain**.

### Usage

**typeof for simple built in types**

```javascript
'example string' instanceof String; // false
typeof 'example string' == 'string'; //true

'example string' instanceof Object; //false
typeof 'example string' == 'object'; //false

true instanceof Boolean; // false
typeof true == 'boolean'; //true

99.99 instanceof Number; // false
typeof 99.99 == 'number'; //true

function() {} instanceof Function; //true
typeof function() {} == 'function'; //true
```

**instanceof for complex built in types and custom types**

```javascript
/regularexpression/ instanceof RegExp; // true
typeof /regularexpression/; //object

[] instanceof Array; // true
typeof []; //object

{} instanceof Object; // true
typeof {}; //object

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

var ClassFirst = function () {};
var ClassSecond = function () {};
var instance = new ClassFirst();
typeof instance; // object
typeof instance == 'ClassFirst'; //false
instance instanceof Object; //true
instance instanceof ClassFirst; //true
instance instanceof ClassSecond; //false 

```
