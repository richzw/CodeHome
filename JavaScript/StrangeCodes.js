f = function() {return true;}; 
g = function() {return false;}; 
(function() { 
   if (g() && [] == ![]) { 
      f = function f() {return false;}; 
      function g() {return true;} 
   } 
})(); 
console.log(f());

// the result is true under firefox, whereas the result is true under Chrome.
/*
此题的关键是第4行的if条件 g() && [] == ![]

这里有三个关键的点，
第一，g()在这里执行的到底是第2行的函数还是第6行的函数？
第二，Javascript里面的falsy值
第三，== 运算符的运算逻辑

先看第一点，我不喜欢卖关子，直接揭晓答案，第4行的g()，执行的是第6行的函数，返回值的是true。

这里的考点是javascript的Execution Context, Variable Object, Scope Chain等概念，
简单来说，Javascript的作用域是函数级别的，并且在函数刚开始执行时，就会对函数体内所有的变量及内部函数进行声明，
不会等到写的那一行，也就是说，即使你一个内部函数写在包含它的函数的最后面，你在第一行也照样用。
回到这道题，我们本来有一个全局的函数g，写在第二行，但是进入第4行，我们进入了一个匿名函数的内部，
这个匿名函数里面又在第6行声明一个局部函数g，于是这个局部函数覆盖了全局函数，因此，第4行调用的是写在第6行的局部函数g。

既然g()返回的true，那么接下来就要看 [] == ![] 这句极诡异的比较式的值，这里是拿一个空数组去跟空数组的取反的值比较，
初看起来肯定是false啊。可惜，它的值是true，请不要崩溃，让我来仔细分析javascript的操蛋的逻辑。

首先我们看右边的 ![]，对一个空数组取反，那么意味着先要把空数组转化为一个boolean值，再取反，
在javascript中，所有对象在作为boolean值使用时，都是表示true，空数组也是一个对象，所以空数组也是true，那么对空数组取反，
等价于 !true，所以，![]的值为false。

好了，既然右边说完了是false，现在我们就等于在看 [] == false，刚才不是说了空数组是对象是true么，
那很明显这个比较就是true == false， 就是返回false对不对？可惜不是，这个比较会返回true，看到这你抓狂了没有
，想不通了有没有？先冷静，我来告诉你发生了什么，根据 ECMAScript的对于==的规范，这样一个表达式最终是这么做的

1.把右边的false转成数值0
2.把左边的对象转成字符串，空数组转成字符串就是空字符串
3.把空字符串转成数值，结果是0
4.比较0 == 0，返回true
这里的关键是第2步，数组会先转成空字符串，空字符其实本身就是一个falsy值。

好了，到底谜底全部解开，第4行的if中的判断为实际上是true && true，结果还是true，于是全局函数f在第5行被重新赋值，
所以在第9行执行的是第5行被重新赋值的f，返回false。

关于第5行其实还有点小问题，为什么这里的function f() {return false;}没有像第6行的函数g一样被当做一个局部函数，
如果这样的话，那么f也是一个局部函数，对f的赋值应该不会影响全局函数f。这里的原因在于，整个第5行不是一个函数声明，
第5行作为一个整体其实是一条赋值语句，所以这里的f不会被当做局部变量。

ECMAScript 5, the current official specification of the JavaScript language, does not define the behavior for function 
declarations inside blocks.

FunctionDeclarations are only allowed to appear in Program or FunctionBody. Syntactically, they can not appear in Block
({ ... }) — such as that of if, while or for statements. This is because Blocks can only contain Statements, 
not SourceElements, which FunctionDeclaration is. If we look at production rules carefully, we can see that the only 
way Expression is allowed directly within Block is when it is part of ExpressionStatement. However, 
ExpressionStatement is explicitly defined to not begin with "function" keyword, and this is exactly why 
FunctionDeclaration cannot appear directly within a Statement or Block (note that Block is merely a list of Statements).

Because of these restrictions, whenever function appears directly in a block (such as in the previous example) 
it should actually be considered a syntax error, not function declaration or expression. 
The problem is that almost none of the implementations I've seen parse these functions strictly per rules
(exceptions are BESEN and DMDScript). They interpret them in proprietary ways instead.

Also worth quoting the ECMAScript 6 draft - B.3.3 Block-Level Function Declarations Web Legacy Compatibility Semantics:

Prior to the Sixth Edition, the ECMAScript specification did not define the occurrence of a FunctionDeclaration as
an element of a Block statement’s StatementList. However, support for that form of FunctionDeclaration was an allowable 
extension and most browser-hosted ECMAScript implementations permitted them. Unfortunately, 
the semantics of such declarations differ among those implementations. [...]

As ES5 does not define the behavior for function declarations inside blocks while allowing proprietary extensions, 
there are technically no "rights" or "wrongs". Consider them "unspecified behavior" which is not portable across 
different ES5-compliant environments.

Those are easy to rewrite into portable code anyway:

Should the function declaration be hoisted to the top of the current function/global scope? Make sure the function 
declaration is not directly inside of a block.
Should the function be declared only when the block executes? Assign a function expression to a variable 
(var f = function() {};). Note that there is no hoisting and the variable is still accessible outside of the block 
(var declarations are function-level scoped).
As per ECMAScript 6, function declarations are block-scoped, so Firefox implements the correct behavior ES6-wise.
*/
