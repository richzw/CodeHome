'use strict';

/**
 * dependencies
 */
var amqp = require('amqplib'),
	when = require('when');


/**
 * Sender Class, initialized with amqp address
 * @param {string} amqpAddr The amqp address
 * @param {number} retryDelay A delay time per milliseconds 
 * @param {number} attempts Retry connection number
 * @param {Function} callback Message send failure callback
 * @constructor
 */
var Sender = function( amqpAddr, retryDelay, attempts, callback ) {
	/**
	 * amqp address
	 * @type {!string}
	 * @private
	 */
	this.addr_ = amqpAddr || 'amqp://localhost';
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

	this.ex_ = 'BS';

	this.retryDelay_ = retryDelay;

	this.attempts_ = attempts;

	this.cb_ = callback;

	this.tryConnect_();
};

/**
 * create connection to amqp.
 * @private
 */
Sender.prototype.createConnection_ = function() {
	return amqp.connect( this.addr_ );
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
	return this.ch_.assertExchange( this.ex_ , 'direct', { durable: true } );
};


/**
 * Handle unrouteable message
 * @private
 */
Sender.prototype.handleUnrouteableMessages_ = function() {
	var self = this;
	return this.ch_.on('return', function( msg ) {
		console.log( 'Sender: Message returned to sender ' + msg.content );
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
			//console.log('Sender: Get Channel Close here');
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
			// err.code == 'ECONNRESET' exception is caught here 

			that.retryConnect_( err );
		};
	})(this));

	return con;
};

/**
 * Handle connection blocked,  if there is some resource shortage, e.g., 
 *		memory, and messages are published on the connection. 
 * 
 */
Sender.prototype.handleConnectionBlock_ = function() {
	this.con_.on('blocked', function( reason ) {
		console.log('Sender: [Error] MessageBus Connection Blocked due to' + reason);
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
 * @param {string} key An argument that represent routing key.
 * @param {object} msg Message wrapped by protocol buffer.  
 * @private
 */
Sender.prototype.publish_ = function( channel, key, msg ) {
	console.log('Sender: [Debug] prepare to publish message');
	channel.publish( this.ex_, key, msg, { deliveryMode: 2, mandatory: true });

	return channel.waitForConfirms()
		.then(function() {
			console.log('Sender: [Debug] publish message processed');
		}, function( err ) {
			console.log('Sender: [Error] publis message ' + err );
			return when.reject( new Error('Sender: Publish Message Error') );
		});
};

/**
 * deliver message to amqp
 * @param {string} key An argument that represent routing key.
 * @param {object} msg Message wrapped by protocol buffer.
 * @public
 */
Sender.prototype.deliverMessage = function ( key, msg ) {
	return this.getConnection_()
		.with( this )
		.then( function( channel ) { 
			this.publish_( channel, key, msg ); 
		})
		.catch( function( err ) {
			// notify sender error to UI client
			this.cb_( key );
		});
};

/**
 * handle the connection exception
 * @return {Object} Current sender or exception error
 * @private
 */
Sender.prototype.handleConnectionException_ = function() {
	try {
		if ( this.con_ !== null ) {
			this.con_.close();
			this.con_ = null;
		}

		if ( this.ch_ !== null ) {
			this.ch_.close();
			this.ch_ = null;
		}
	} catch ( ex ) {
		return when.reject( new Error('Sender: handldConnectionException_ Error') );
	}

	return when.resolve( this );
};

/**
 * retry connect to amqp.
 * @param {number} retryDelay A delay time per milliseconds
 * @param {Object} err Error object
 * @private
 */
Sender.prototype.retryConnect_ = function( err ) {
	console.error('Sender: MessageBus disconnected, attempted to reconnect.' + err);

	return when( this.handleConnectionException_() )
		.with( this )
		.delay( this.retryDelay_ )
		.then( function() {
			return this.tryConnect_();
		})
		.catch( function( e ) {
			console.log('Sender: [Error] connection' + e);
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

