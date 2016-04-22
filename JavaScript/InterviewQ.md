
[http://www.ido321.com/1660.html?hmsr=toutiao.io&utm_medium=toutiao.io&utm_source=toutiao.io](http://www.ido321.com/1660.html?hmsr=toutiao.io&utm_medium=toutiao.io&utm_source=toutiao.io)


```javascript
Number.isInteger = Number.isInteger || function(value) {
    return typeof value === "number" && 
           isFinite(value) && 
           Math.floor(value) === value;
};
```

```javascript
function isPalindrome(str) {
    str = str.replace(/\W/g, '').toLowerCase();
    return (str == str.split('').reverse().join(''));
}
```

Source:

- [quiz 1](http://kourge.net/node/130)
- [quiz 2](http://perfectionkills.com/javascript-quiz/)
- [interview question](https://www.toptal.com/javascript/interview-questions)







