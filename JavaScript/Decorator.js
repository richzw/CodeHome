/*
A function decorator accepts a function, 
wraps (or decorates) it’s call and returns the wrapper, which alters default behavior.
*/

function checkPermissionDecorator(f) {
  return function() {
    if (user.isAdmin()) f() 
    else alert('Not an admin yet')
  }
}

// Usage: make save check permissions

save = checkPermissionDecorator(save)

// Now save() calls will check permissions


function doublingDecorator(f) {        // (1)
  return function() {
    return 2*f.apply(this, arguments)
  } 
}

// Usage:
function sum(a, b) {
  return a + b
}

var doubleSum = doublingDecorator(sum)          // (2)

alert( doubleSum(1,2) ) // 6
alert( doubleSum(2,3) ) // 10

