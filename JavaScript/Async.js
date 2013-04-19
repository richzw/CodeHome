// several implementation of async in javascript

(function() {
  var Async;
 
  Async = (function() {
 
    function Async() {
      this.callbacks = [];
      this.running = false;
    }
 
    Async.prototype.series = function(func) {
      if (this.running) {
        this.callbacks.push(func);
      } else {
        this.running = true;
        func();
      }
    };
 
    Async.prototype.callback = function() {
      if (this.callbacks.length > 0) {
        this.callbacks.shift()();
      } else {
        this.running = false;
      }
    };
 
    return Async;
 
  })();
 
  window.Async = Async;
 
}).call(this);
 
 
 var x = 56;
 xss_rpc_call(x, function(result){
     alert(x + "," + result);
 });
 
 //the problem we should solved.
 var total = 20;
 for (var i = 0; i < total; ++i){
     xss_rpc_call(i, function(result){
         alert(i + "," + result);
     });
 }
 
 //recursive solution
 function recursive_solution(i){
     if (i >= total)
         return;
 
     xss_rpc_call(i, function(result){
         alert(i + ", " + result);
 
         recursive_solution(i + 1);
     });
 }
 
 //closure solution
 function closure_solution(){
     for (var i = 0; i < total; ++i){
         (function(x){
             xss_rpc_call(x, function(result){
                 console.log(x + "," + result);
             });
         })(i);
     }
 }
 
 //async solution
 function async_solution(){
     var async = new Async();
 
     for (var i = 0; i < total; ++i){
         async.series((function(index){
             xss_rpc_call(index, function(result){
                 display_result(index + "," + result);
                 async.callback();
             });
         }).bind(null, i));
     }
 }
