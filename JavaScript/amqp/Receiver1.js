'use strict';

/**
 * dependencies
 */
var amqp = require('amqplib'),
	when = require('when');

/**
 * Receiver Class, initialized with amqp address
 * @param {string} amqpAddr The amqp address
 * @param {number} retryDelay A delay time per milliseconds
 * @param {Function} callback Message consumer callback function
 * @constructor
 */
var Receiver = function( amqpAddr, retryDelay, callback ) {
	/**
	 *
	 */
	this.amqpAddr_ = amqpAddr;

	this.retryDelay_ = retryDelay;

	this.con_ = null;

	this.ch_ = null;

	this.ex_ = 'direct_UI';

	this.queueName_ = 'UI';

	this.cb_ = callback;

	this.connect_();
};

/**
 * create channel to amqp.
 * @param {Object} con Amqp connection
 * @private
 */
Receiver.prototype.createChannel_ = function( con ) {
	this.con_ = con;
	return this.con_.createConfirmChannel();
};

/**
 * create exchange for amqp in direct way.
 * @param {Object} ch Amqp channel
 * @private
 */
Receiver.prototype.createExchange_ = function( ch ) {
	this.ch_ = ch;
	return this.ch_.assertExchange( this.ex_ , 'direct', { durable: true } );
};

/**
 * create queue for amqp
 * @private
 */
Receiver.prototype.createQueue_ = function() {
	return this.ch_.assertQueue( this.queueName_, { exclusive: true } );
};

/**
 * bind queue for amqp
 * @private
 */
Receiver.prototype.bindQueue_ = function( qok ) {
	var queue = qok.queue;
	return this.ch_.bindQueue( queue, this.ex_, this.queueName_ )
		.then(function() {
			return queue;
		});
};


/**
 * set up consume callback for amqp
 * @param {Object} queue Message queue in amqp
 * @private
 */
Receiver.prototype.consume_ = function( queue ) {
	return this.ch_.consume( queue, this.cb_, { noAck: true } );
};

/**
 * handle disconnection failure
 * @private
 */
Receiver.prototype.handleDisconnection_ = function() {
	return this.con_.on('error', (function( that ) {
		return function( err ) {
			return that.reconnect_( err );
		};
	})(this));
};

/**
 *
 */
Receiver.prototype.handleChannelError_ = function() {
	return this.ch_.on('error', (function( that ) {
		return function( err ) {
			return that.reconnect_( err );
		}
	})(this));
}


/**
 * handle the connection exception
 * 
 */
Receiver.prototype.handldConnectionException_ = function() {
	try {
		if (this.con_ !== null) {
			this.con_.close();
			this.con_ = null;
		}

		if (this.ch_ !== null) {
			this.ch_.close();
			this.ch_ = null;
		}
	} catch ( ex ) {
		return when.reject( new Error('Receiver: handldConnectionException_ Error') );
	}

	return when.resolve( this );
};

/**
 * try to reconnect to amqp
 * @private
 */
Receiver.prototype.reconnect_ = function( err ) {
	console.error('Receiver: MessageBus disconnected, attempted to reconnect.' + err);
	return when( this.handldConnectionException_() )
		.with( this )
		.delay( this.retryDelay_ )
		.then( function() {
			return this.connect_();
		})
		.catch( function( e ) {
			console.log('Receiver: [Err] connection exception: ' + e);
			return this.connect_();
		});
};

/**
 * connect to amqp
 * @private
 */
Receiver.prototype.connect_ = function() {
	return when( amqp.connect( this.amqpAddr_ ) )
		.with( this )
		.then( this.createChannel_ )
		.then( this.createExchange_ )
		.then( this.createQueue_ )
		.then( this.bindQueue_ )
		.then( this.consume_ )
		.then( this.handleDisconnection_ )		
		.then( this.handleChannelError_ )
		.catch( function( err ) {
			return this.reconnect_( err );
		});
};

/**
 * exports
 */
module.exports = exports = Receiver;
