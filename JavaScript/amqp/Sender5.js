'use strict';

/**
 * Cache module to interact with Redis Cache
 * @module network/sender
 */
var amqp = require('amqplib'),
	when = require('when'),
	_ = require('lodash');


/**
 * Sender Class, message sender to amqp
 * @param {Object} config The amqp sender configuration
 */
var Sender = function( config ) {
	/**
	 * amqp address
	 * @type {!string}
	 * @private
	 */
	var defaultUrl = {
		userName: 'guest',
		password: 'guest',
		host: 'localhost',
		port: 5672,
		vHost: '',
	};
	config.url = _.extend(defaultUrl, config.url);

	this.amqpUrl_= 'amqp://' + config.url.userName + ':'
		+ config.url.password + '@'
		+ config.url.host + ':'
		+ config.url.port
		+ config.url.vHost;

	console.log('[Sender]: The url is ' + this.amqpUrl_);

	var defaultConnectOpt = {
		'noDelay': true,
		'channelMax': 0,
		'frameMax': 0,
		'heartbeat': 0, // per second
	};
	this.connectOpt_ = _.extend( defaultConnectOpt, config.connectOpt );

	var defaultExchangeOpt = {
		'durable': true,
		'internal': false,
		'autoDelete': false,
	};
	this.exchangeOpt_ = _.extend( defaultExchangeOpt, config.exchangeOpt );

	var defaultPublishOpt = {
		'mandatory': true,
		'deliveryMode': 2
	};
	this.publishOpt_ = _.extend( defaultPublishOpt, config.publishOpt );

	/**
	 * amqp channel
	 * @type {Object}
	 * @private
	 */
	this.ch_ = null;
	/**
	 * amqp connection
	 * @type {Object}
	 * @private
	 */
	this.con_ = null;
	/**
	 * exchange name
	 * @type {string}
	 * @private
	 */
	this.ex_ = config.senderConfig.exchangeName || 'BS';

	/**
	 * rpc queue name
	 * @type {string}
	 * @private
	 */
	this.rpcQueueName_ = config.senderConfig.rpcQueueName;

	this.rpcQueue_ = null;

	this.baseHostQueue_ = config.senderConfig.baseHostQueueName;

	this.key_ = config.senderConfig.baseRoutingKey || 'BS';
	/**
	 * retry delay time
	 * @type {number}
	 * @private
	 */
	this.retryDelay_ = config.senderConfig.retryDelay || 3000;
	/**
	 * message send failure callback
	 * @type {Function}
	 * @private
	 */
	this.cb_ = config.callback;

	// try to connect with amqp
	this.tryConnect_();
};

/**
 * create connection to amqp.
 * @private
 */
Sender.prototype.createConnection_ = function() {
	return amqp.connect( this.amqpUrl_, this.connectOpt_ );
};

/**
 * create channel to amqp.
 * @param {Object} con Amqp connection
 * @private
 */
Sender.prototype.createChannel_ = function( con ) {
	this.con_ = con;
	return this.con_.createConfirmChannel();
};

/**
 * create exchange for amqp in direct way.
 * @param {Object} ch Amqp channel
 * @private
 */
Sender.prototype.createExchange_ = function( ch ) {
	this.ch_ = ch;
	return this.ch_.assertExchange( this.ex_ , 'direct', this.exchangeOpt_ );
};


/**
 * create rpc queue
 * @private
 */
Sender.prototype.createRPCQueue_ = function() {
	return this.ch_.assertQueue(this.rpcQueueName_, {exclusive: false});
};

/**
 * Handle unrouteable message
 * @private
 */
Sender.prototype.handleUnrouteableMessages_ = function() {
	var self = this;
	return this.ch_.on('return', function( msg ) {
		console.error( 'Sender: Message returned to Sender ' + msg.content );
		return self;
	});
};

/**
 * Handle channel error
 * @private
 */
Sender.prototype.handleChannelClose_ = function() {
	return this.ch_.on('close', (function( that ) {
		return function( err ) {
			return that;
		}
	})(this));
}

/**
 * Handle amqp channel error.
 * @param {Object} ch Amqp channel
 * @private
 */
Sender.prototype.handleChannelError_ = function( ch ) {
	this.ch_ = ch;

	this.ch_.on('error', (function( that ) {
		return function( err ) {
			that.retryConnect_( err );
		};
	})(this));

	return ch;
}

/**
 * Handle amqp disconenction and try to reconnect.
 * @param {Object} con Amqp connection
 * @private
 */
Sender.prototype.handleConnectionError_ = function( con ) {
	this.con_ = con;

	this.con_.on('error', (function( that ) {
		return function( err ) {
			// Note: err.code == 'ECONNRESET' exception is caught here

			that.retryConnect_( err );
		};
	})(this));

	return con;
};

/**
 * Handle connection blocked,  if there is some resource shortage, e.g.,
 *		memory, and messages are published on the connection.
 * @private
 */
Sender.prototype.handleConnectionBlock_ = function() {
	this.con_.on('blocked', function( reason ) {
		console.error('Sender: MessageBus Connection Blocked due to' + reason);
	});

}

/**
 * Handle amqp connection close
 * @private
 */
Sender.prototype.handleConnectionClose_ = function() {
	return this.con_.on('close', (function( that ) {
		return function( err ) {
			return that;
		}
	})(this));
};

/**
 * Get amqp connection
 * @return {Object} Amqp connection or connection failure error
 * @private
 */
Sender.prototype.getConnection_ = function() {
	if ( this.ch_ === null ) {
		return when.reject( new Error('Sender: MessageBus Connection Failed Now') );
	} else {
		return when.resolve( this.ch_ );
	}
};

/**
 * publish message to amqp
 * @param {Object} channel The channel to publish message.
 * @param {string} key An argument that crepresent routing key.
 * @param {object} msg Message wrapped by protocol buffer.
 * @private
 */
Sender.prototype.publish_ = function( channel, key, msg, cb ) {
	channel.publish( this.ex_, key, msg, this.publishOpt_ );

	return channel.waitForConfirms()
		.then(function() {
			console.log('Sender: published message is processed');
			cb && cb(null, key);
		}, function( err ) {
			console.error('Sender: publish message ' + err );
			return when.reject( new Error('Sender: Publish Message Error') );
		});
};

/**
 * deliver message to amqp
 * @param {string} key An argument that represent routing key.
 * @param {object} msg Message wrapped by protocol buffer.
 * @public
 */
Sender.prototype.deliverMessage = function ( key, msg, cb ) {
	key = this.key_ + key;

	return this.getConnection_()
		.with( this )
		.then( function( channel ) {
			this.publish_( channel, key, msg, cb );
		})
		.catch( function( err ) {
			console.error( err );
			this.cb_ && this.cb_( key );
			cb && cb(err, key);
		});
};

/**
 * deliver message by rpc
 * @param {string} key An argument that represent routing key.
 * @param {object} msg Message wrapped by protocol buffer.
 * @param {function} cb rpc callback function
 * @public
 */
Sender.prototype.deliverMessageByRPC = function( key, corrId, msg, cb ) {
	// cancel the consumer tag first
	return this.ch_.cancel('RPC')
		.with(this)
		.then(function() { return this.ch_; })
		.then(function(ch) {
			ch.consume( this.rpcQueue_, cb, {noAck: true, consumerTag: 'RPC'} );
		})
		.then(function() { return this.rpcQueue_; })
		.then(function(queue) {
			this.ch_.sendToQueue(this.baseHostQueue_ + key, msg, {
        correlationId: corrId, 
        replyTo: queue	
			});
		})
		.catch(function(err) {
			console.error(err);
			cb && cb(err);
		});
};

/**
 * retry connect to amqp.
 * @param {number} retryDelay A delay time per milliseconds
 * @param {Object} err Error object
 * @private
 */
Sender.prototype.retryConnect_ = function( err ) {
	console.error('Sender: MessageBus disconnected, attempted to reconnect.' + err);

	return when( 'retry' )
		.with( this )
		.delay( this.retryDelay_ )
		.then( function() {
			return this.tryConnect_();
		})
		.catch( function( err ) {
			console.error('Sender: Connection' + err);
			return this.tryConnect_();
		});

};

/**
 * Try to connect to amqp.
 * @private
 */
Sender.prototype.tryConnect_ = function() {
	return when( this.createConnection_() )
		.with( this )
		.then( this.handleConnectionError_ )
		.then( this.createChannel_ )
		.then( this.handleChannelError_ )
		.then( this.createExchange_ )
		.then( this.handleUnrouteableMessages_ )
		.then( this.createRPCQueue_ )
		.then( function(qok) {
			this.rpcQueue_ = qok.queue;
		})
		//.then( this.handleConnectionClose_ )
		//.then( this.handleChannelClose_ )
		.catch( function( e ) {
			return this.retryConnect_( e );
		});
};

/**
 * exports
 */
module.exports = exports = Sender;

