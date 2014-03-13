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
