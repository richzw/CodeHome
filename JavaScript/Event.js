var util = require('util'),
  EventEmitter = require('events').EventEmitter;

var Host = function(ho) {
  var self = this;
  EventEmitter.call(this);
  
  this.on('ev1', function(param) {
    
  });
  
  
};

util.inherits(Host, EventEmitter);
var h = new Host();

h.emit('ev1', param);
