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

*/
