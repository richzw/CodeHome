// output?
(function() {
   var a = b = 5;
})();
console.log(b);

(function() {
   'use strict';
   var a = window.b = 5;
})();
console.log(b);

// add repeatify method to String like  console.log('hello'.repeatify(3));
String.prototype.repeatify = String.prototype.repeatify || function(times) {
   var str = '';
   for (var i = 0; i < times; i++) {
      str += this;
   }
   return str;
};

// what output?
var fullname = 'John Doe';
var obj = {
   fullname: 'Colin Ihrig',
   prop: {
      fullname: 'Aurelio De Rosa',
      getFullname: function() {
         return this.fullname;
      }
   }
};
console.log(obj.prop.getFullname());  // 'Aurelio De Rosa'
var test = obj.prop.getFullname;
console.log(test()); // 'John Doe'

// fix it to console.log(test.call(obj.prop))  


// 传入一个string类型的参数，然后将string的每个字符间加个空格返回
  function spacify(str) {
      return str.split('').join(' ');
    }
    
// 如何把这个方法放入String对象上面
  String.prototype.spacify = function(){
      return this.split('').join(' ');
    };
    
// 定义一个未定义的log方法作为开始
function log(msg)　{
      console.log(msg);
    }
    
// 改变我调用log的方式，传入多个参数
function log(){
      console.log.apply(console, arguments);
    };

//给每一个log消息添加一个"(app)"的前辍, '(app) hello world'
    function log(){
      var args = Array.prototype.slice.call(arguments);
      args.unshift('(app)');

      console.log.apply(console, args);
    };

//////////////////////////////////////////////////////////////
var User = {
  count: 1,

  getCount: function() {
    return this.count;
  }
};

console.log(User.getCount());

    var func = User.getCount;
    console.log(func());
    
// output: 答案是1和undefined。

// 怎么样保证User总是能访问到func的上下文，即返回正即的值：1
var func = User.getCount.bind(User);
    console.log(func());
    
Function.prototype.bind = Function.prototype.bind || function(context){
      var self = this;

      return function(){
        return self.apply(context, arguments);
      };
    }    

//在遮罩中最好使用position中的fixed代替absolute属性，这样即使在滚动的时侯，也能始终让遮罩始盖住整个窗口。
//当侯选人忽略时我会提示他们这一点，并让他们解释fixed和absolute定位的区别。
   .overlay {
      position: fixed;
      left: 0;
      right: 0;
      bottom: 0;
      top: 0;
      background: rgba(0,0,0,.8);
    }
//他们如何让里面的内容居中也是需要考察的一点。一些侯选人会选择CSS和绝对定位，如果内容有固定的宽、高这是可行的。
//否则就要使用JavaScript.
  .overlay article {
      position: absolute;
      left: 50%;
      top: 50%;
      margin: -200px 0 0 -200px;
      width: 400px;
      height: 400px;
    }
//我也会让侯选人确保当遮罩被点击时要自动关闭，这会很好地考查事件冒泡机制的机会
//。通常侯选人会在overlay上面直接绑定一个点击关闭的方法。
  $('.overlay').click(closeOverlay);
//这是个方法，不过直到你认识到点击窗口里面的东西也会关闭overlay的时侯——这明显是个BUG。
//解决方法是检查事件的触发对象和绑定对象是否一致，从而确定事件不是从子元素里面冒上来的，就像这样：
   $('.overlay').click(function(e){
      if (e.target == e.currentTarget)
        closeOverlay();
    });

