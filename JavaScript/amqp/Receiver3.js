'use strict';

/**
 * dependencies
 */
var amqp = require('amqplib'),
	when = require('when'),
	_ = require('lodash');

/**
 * Receiver Class, message receiver from amqp
 * @param {Object} config The amqp receiver configuration
 * @constructor
 */
var Receiver = function( config ) {
	/**
	 * amqp address
	 * @type {!string}
	 * @private
	 */
	this.amqpUrl_ = config.amqpUrl || 'amqp://localhost';
	/**
	 * retry delay time
	 * @type {number}
	 * @private
	 */	
	this.retryDelay_ = config.retryDelay || 3000;

	var defaultConnectOpt = {
		'noDelay': true,
		'channelMax': 0,
		'frameMax': 0,
		'heartbeat': 0, // per second
	};
	this.connectOpt_ = _.extend( defaultConnectOpt, config.connectOpt );	

	var defaultQueueOpt = {
		'exclusive': true,
		'durable': true,
		'autoDelete': false,
	};

	this.queueOpt_ = _.extend( defaultQueueOpt, config.queueOpt );

	var defaultExchangeOpt = {
		'durable': true,
		'internal': false,
		'autoDelete': false,
	};
	this.exchangeOpt_ = _.extend( defaultExchangeOpt, config.exchangeOpt );

	var defaultConsumeOpt = {
		'consumerTag': 'BONUSUI',
		'noLocal': false,
		'noAck': true,
		//'exclusive': true,
	};
	this.consumerOpt_ = _.extend( defaultConsumeOpt, config.consumerOpt );

	/**
	 * amqp connection
	 * @type {Object}
	 * @private
	 */	
	this.con_ = null;
	/**
	 * amqp channel
	 * @type {Object}
	 * @private
	 */
	this.ch_ = null;
	/**
	 * exchange name
	 * @type {string}
	 * @private
	 */
	this.ex_ = config.exchangeName || 'UI';
	/**
	 * queue name
	 * @type {string}
	 * @private
	 */
	this.queueName_ = config.queueName || 'UI';
	/**
	 * message receiver callback
	 * @type {Function}
	 * @private
	 */	
	this.cb_ = config.callback;

	// try to connect with amqp
	this.connect_();
};

/**
 * create connection to amqp
 * @private
 */
Receiver.prototype.createConnection_ = function() {
	return amqp.connect( this.amqpUrl_, this.connectOpt_ );
}

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
	return this.ch_.assertExchange( this.ex_ , 'direct', this.exchangeOpt_ );
};

/**
 * create queue for amqp
 * @private
 */
Receiver.prototype.createQueue_ = function() {
	return this.ch_.assertQueue( this.queueName_, this.queueOpt_ );
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
	return this.ch_.consume( queue, this.cb_, this.consumerOpt_ );
};

/**
 * handle connection error
 * @param {Object} con Amqp connection 
 * @return {Object} The amqp connection
 * @private
 */
Receiver.prototype.handleConnectionError_ = function( con ) {
	this.con_ = con;

	this.con_.on('error', (function( that ) {
		return function( err ) {
			that.reconnect_( err );
		};
	})(this));

	return con;
};

/**
 * handle channel error
 * @param {Object} ch Amqp channel
 * @return {Object} The amqp channel
 * @private
 */
Receiver.prototype.handleChannelError_ = function( ch ) {
	this.ch_ = ch;

	this.ch_.on('error', (function( that ) {
		return function( err ) {
			that.reconnect_( err );
		}
	})(this));

	return ch;
}


/**
 * try to reconnect to amqp
 * @private
 */
Receiver.prototype.reconnect_ = function( err ) {
	console.error('Receiver: MessageBus disconnected, attempted to reconnect.' + err);

	return when( 'retry' )
		.with( this )
		.delay( this.retryDelay_ )
		.then( function() {
			return this.connect_();
		})
		.catch( function( e ) {
			console.error('Receiver: MessageBuf connection exception: ' + e);
			return this.connect_();
		});
};

/**
 * connect to amqp
 * @private
 */
Receiver.prototype.connect_ = function() {
	return when( this.createConnection_() )
		.with( this )
		.then( this.handleConnectionError_ )
		.then( this.createChannel_ )
		.then( this.handleChannelError_)
		.then( this.createExchange_ )
		.then( this.createQueue_ )
		.then( this.bindQueue_ )
		.then( this.consume_ )
		.catch( function( err ) {
			return this.reconnect_( err );
		});
};

/**
 * exports
 */
module.exports = exports = Receiver;
