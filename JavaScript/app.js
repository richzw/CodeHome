var dgram = require("dgram");
var server = dgram.createSocket('udp4');
var redis = require("redis");
var client = redis.createClient();
_ = require('underscore')._;
var amqp = require('amqp');

/*
var amqp_option = { 
	host: 'localhost'
	, port: 5672
	, login: 'guest'
	, password: 'guest'
	, authMechanism: 'AMQPLAIN'
	, vhost: '/'
	, ssl: { enabled : false
       }
};*/
var connection = amqp.createConnection();
var queue;
var exchange;
connection.on('ready', function(){
	exchange = connection.exchange('json-fanout', {type: 'fanout'});
	
	queue = connection.queue('json-queue', function(q){
		console.log('create queue success...');
		
		q.bind(exchange, "*");
		
		q.subscribe(function(json, headers, deliveryInfo){
			switch(deliveryInfo.routingKey){
				case "message.meter":
					console.dir(json);
				break;
				default:
					console.log("unexpected routing key: "+deliveryInfo.routingKey);
			}
		});
	});
});
connection.on('error', function(err){
	console.log('rabbitmq connection error: '+err);
});
connection.on('close', function(e){
	console.log('rabbitmq connection close: '+e);
});

client.on("error", function(err){
	console.error("Redis error "+err);
});

var parseMeters = function(msg, dcn_count){
	var egms = [];	
	
	// parsing dcn meter information iteratively
	for (var dcn_index = 0; dcn_index < dcn_count; ++dcn_index){
		var egm = {};
		egm.uid = msg.readUInt32LE(28 + 40*dcn_index + 2);
		egm.floor_location = msg.toString('utf8', (28+40*dcn_index+6), (28+40*dcn_index+14));
		egm.coin_meter = msg.readUInt32LE(28+40*dcn_index+20);
		egm.card_meter = msg.readUInt32LE(28+40*dcn_index+36);
		egm.status = msg[28+40*dcn_index+18];
		
		egms.push(egm);
	}
	//console.log("server got:" + msg);
	return egms;
};

var saveMeters = function(egms, callback){
	var rabbit_egms = [];	
	var egm_count = 0;
	
	_.each(egms, function(egm){
		client.hvals(JSON.stringify(egm.uid), function(err, replies){
			if (err){
				return console.error("error replies: "+err);
			}
			
			// compute the meter delta value
			if (!err && replies){
				var data = {};
				data.uid = egm.uid;
				data.coin_delta = egm.coin_meter - replies[1];
				data.card_delta = egm.card_meter - replies[2];
				data.status = egm.status;
				
				rabbit_egms.push(data);
			}
			
			//save the new meter into redis
			client.hmset(JSON.stringify(egm.uid), "floor_location", JSON.stringify(egm.floor_location));
			client.hmset(JSON.stringify(egm.uid), "coin_meter", JSON.stringify(egm.coin_meter));
			client.hmset(JSON.stringify(egm.uid), "card_meter", JSON.stringify(egm.card_meter));	
			client.hmset(JSON.stringify(egm.uid), "status", JSON.stringify(egm.status));
			
			++egm_count;
			if (egm_count >= egms.length){
				callback(rabbit_egms);
			}		
		});
	});
};

var output_rabbitmq = function(egms){
	_.each(egms, function(egm){
		if (exchange){
			exchange.publish('message.meter', egm, {contentType: 'application/json'});
		}		
	});
}

server.on("message", function(msg, rinfo){
	// filter the Ag3MeterBroadcastMsg accroding to the packet type and message type
	if(msg[18] === 1 && msg[19] === 2){
		var dcn_count = msg.readUInt16LE(26);
		
		// parse meters from meter broadcast message
		var egms = parseMeters(msg, dcn_count);
		
		// save meter infor into redis
		saveMeters(egms, output_rabbitmq);
	}
	
});

server.on("error", function(ex){
	console.error("server got error: "+ex);
});

server.on("end", function(ex){
	console.log("redis server connection closed: "+ex);
});

server.on("listening", function(){
	var address = server.address();
	console.log("server listening "+ address.address +":"+address.port);
});

server.bind(10009, function(){
	//server.addMembership('172.16.63.50', 'Local Area Connection 2');
});

//server.quit();
