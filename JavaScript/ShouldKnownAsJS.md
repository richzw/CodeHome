[Must Known In JavaScript](http://stackoverflow.com/questions/2628672/what-should-every-javascript-programmer-know)
==========

- That object.prop and object['prop'] are the same thing (so can you please stop using eval, thanks); that object properties are always strings (even for arrays); what for...in is for (and what it isn't).

    方括号可以通过变量来访问属性
    
    ```javascript
    person.name;
    person['name'];
    var propertyName = 'name';
    person[propertyName]; 
    // name
    ```
    
    当属性是带空格的string时就只能用方括号了：person['first name'];
    
    for…in 循环输出的属性名顺序不可预测,使用之前先检测对象是否为null 或者 undefined
    
    ------------

- Property-sniffing; what undefined is (and why it smells); why the seemingly-little-known in operator is beneficial and different from typeof/undefined checks; hasOwnProperty; the purpose of delete.

    undefined好理解一般用来表示未定义，而且不能用delete来删除它。
    
    null 表示一个空对象指针 所以 typeof null返回 object
    
    undefined派生自null alert(null == undefined) 返回true; 但alert(null === undefined)就返回false了
    
    **hasOwnProperty是js中唯一一个处理属性但是不查找原型链的函数**
    
    -------------

- That the Number datatype is really a float; the language-independent difficulties of using floats; avoiding the parseInt octal trap.



- Nested function scoping; the necessity of using var in the scope you want to avoid accidental globals; how scopes can be used for closures; the closure loop problem.


- How global variables and window properties collide; how global variables and document elements shouldn't collide but do in IE; the necessity of using `var` in global scope too to avoid this.


- How the function statement acts to `hoist` a definition before code preceding it; the difference between function statements and function expressions; why named function expressions should not be used.



- How constructor functions, the prototype property and the new operator really work; methods of exploiting this to create the normal class/subclass/instance system you actually wanted; when you might want to use closure-based objects instead of prototyping. (Most JS tutorial material is absolutely terrible on this; it took me years to get it straight in my head.)

- How this is determined at call-time, not bound; how consequently method-passing doesn't work like you expect from other languages; how closures or Function#bind may be used to get around that.

- Other ECMAScript Fifth Edition features like indexOf, forEach and the functional-programming methods on Array; how to fix up older browsers to ensure you can use them; using them with inline anonymous function expressions to get compact, readable code.

    ```javascript
    Array.prototype.indexOf(searchString ,position)
        var data = [1,3,5,7,9];
        console.log(data.indexOf(5)); 
    //2
        console.log(data.indexOf(5,4)); 
    //-1  从4号位开始搜索
        console.log(data.indexOf('7'));  
    //-1  7!== '7'
     
    Array.prototype.lastIndexOf 
    //从末尾开始查找
    Array.prototype.some 
    //某些条件符合
        var arr = [1,2,3,4,11];
        function larger(item){
            return item> 10    
        }
        console.log(arr.some(larger)?'ok':'no...');
        
    //注：只要有一条符合 即返回true 不再执行
     
    Array.prototype.every 
    // all符合  和some相比就是返回的 true 和 false 调换一下
     
    Array.prototype.forEach 
    //类似jQ里的each
        [1, 2 ,3, 4].forEach(alert);
        [1, 2 ,3, 4].forEach(console.log);
    //FF下运行 不知为什么chrome不行。。。。。
     
    Array.prototype.map 
    //映射 类似forEach 把原数组映射成新数组
        var arr = [1,3,5,7];
        var result = arr.map(function(item){
            return item * item;
        });
        console.log(result); 
    //求各项平方
     
    Array.prototype.filter 
    //筛选
        var filter = [0,2,3,0,undefined].filter(function(item){
            return item;
        });
        console.log(filter);
        
    //filter的callback函数需要返回值为 true 或 false。若为false则过滤掉
     
    Array.prototype.reduce 
    //不是减少  是一种迭代
        var sum = [1,2,3,4,5].reduce(function(pre,current,index,array) {
            return pre + current;
        });
    console.log(sum); 
    //15
     
    Array.prototype.reduceRight 
    //right 自然是从数组末未开始
    ```
    
    ---------

- The flow of control between the browser and user code; synchronous and asynchronous execution; events that fire inside the flow of control (eg. focus) vs. events and timeouts that occur when control returns; how calling a supposedly-synchronous builtin like alert can end up causing potentially-disastrous re-entrancy.

- How cross-window scripting affects instanceof; how cross-window scripting affects the control flow across different documents; how postMessage will hopefully fix this.

