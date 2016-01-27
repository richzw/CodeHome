var assert = require('assert');
var util = require('util');

function NotFoundError(message) {
  Error.call(this);
  this.message = message;
}

util.inherits(NotFoundError, Error);

var error = new NotFoundError('/bitcoin-wallet not found');

assert(error.message);
assert(error instanceof NotFoundError);
assert(error instanceof Error);
assert.equal(error instanceof RangeError, false);

function NotFoundError(message) {
  Error.call(this);
  Error.captureStackTrace(this, arguments.callee);
  this.message = message;
  this.statusCode = 404;
}

// One hacky way to do this is using debug context:
const vm = require('vm');
const Debug = vm.runInDebugContext('Debug'); // Obtain Debug object

Debug.setListener((type, _, e) => { // listen for all debug events
  if (type == Debug.DebugEvent.Exception) {
    console.log(e.exception().stack) // e is an event object
  }
});

Debug.setBreakOnException(); // this is required for Exception event to fire

try {
  throw new Error('bla');
} catch(e) {
  // ha
}
//Warning: don't leave this code in production, use for debugging only.

//Another way is to replace possible error constructors:
const OldError = Error;
const MyError = function(message) {
  const err = new OldError(message);
  OldError.captureStackTrace(err, MyError); // remove top frame from stack trace

  console.log(err.stack);

  return err;
}

MyError.prototype = Error.prototype; // Fix instanceof
global.Error = MyError;

try {
  throw new Error('bla');
} catch(e) {
  
}
new Error('blabla');

// If you are interested only in promises and you are using native v8 promises, then you can try this:

const vm = require('vm');
const Debug = vm.runInDebugContext('Debug');

Debug.setListener((type, _, e) => {
  if (type == Debug.DebugEvent.PromiseEvent) {
    if (e.status() === -1) { // 0=pending, 1=resolved, -1=rejected
      console.log(e.value().value().stack);
    }
  }
});

Promise.reject(new Error('test'))
  .catch(() => {});

