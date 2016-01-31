
// replication lag via serverStatus()
db._adminCommand( { serverStatus : 1 , repl ; 2 } )

// stats
db.stats()
db.foo.stats()

// size of BSON of some query
Object.bsonsize(db.foo.findOne())

// block positioning
var arr=db.test.find({}, {'$diskLoc': 1}).limit(20).showDiskLoc()
for(var i=0; i<arr.length(); i++) {
    printjson(arr[i].$diskLoc.offset/512)
 }

// see running queries
db.currentOp()

// run OS command
runProgram("ls", "-l")

// looping in JS
for (var i=1; i<=1000;i++) 
  db.foo.save({_id:i,"data":"some data here"})

// iterate over all collections:
var arr=db.system.namespaces.find()
for (var i=0; i<arr.length(); i++){
   printjson(arr[i].name)
}

// running a js file on the filesystem
> load("foo.js")
{ "foo" : 1 }


// for each collection, run .stats() against it
var arr=db.system.namespaces.find()
for (var i=0; i<arr.length(); i++){
   var collectionname=arr[i].name.split(".");
   var c="db."+collectionname[1]+".stats()";
   var r=eval(c);
   printjson(r);
}

db.getCollectionNames().forEach(function (z) {print(z, db.getCollection(z).stats()["count"])});

// counting gridfs calls per collection
db.runCommand( "top" ).totals["test.fs.files"] 

// get all db names:
db.getMongo().getDBNames()

var arr = db.getMongo().getDBNames();
for ( i in arr ) {
	c = db.getSiblingDB(arr[i]).stats();
	var r=eval(c);
	printjson(r);
}

// get all collection names
db.system.namespaces.find()

// get profiler data
db.system.profile.find( { info: /test.foo/ } ).sort({millis:-1,$ts:-1})

// simple m/r
// items in collection grouped by userid

var map = function() {
  emit(this.userid, this.sum);
};

var reduce = function(key, values) {
  var sum = 0;
  values.forEach(function(doc) {
    sum += 1;
  });
  return {count: sum};
};

var op = db.SOURCE.mapReduce(map, reduce);
var arr = db[op.result].find();
for (var i=0; i<arr.length(); i++){
   printjson(arr[i])
}

// distinct key count
var arr=db.SOURCE.distinct("userid");
printjson(arr.length);

// reconfigure a replica set:
> cfg=rs.conf()
{
	"_id" : "sfly",
	"version" : 7,
	"members" : [
		{
			"_id" : 0,
			"host" : "al07:27017"
		},
		{
			"_id" : 1,
			"host" : "al06:27017"
		},
		{
			"_id" : 3,
			"host" : "al05:27017",
			"arbiterOnly" : true
		}
	]
}
> cfg['members'][2]['votes']=2;  
2
> cfg
{
	"_id" : "sfly",
	"version" : 7,
	"members" : [
		{
			"_id" : 0,
			"host" : "al07:27017"
		},
		{
			"_id" : 1,
			"host" : "al06:27017"
		},
		{
			"_id" : 3,
			"host" : "al05:27017",
			"arbiterOnly" : true,
			"votes" : 2
		}
	]
}
> rs.reconfig(cfg); 

// query a slave in shell
db.getMongo().setSlaveOk()


// iterate over a results set calling a function in 1 statement
coll.find({},{lid:1}).forEach(fn);

// connection symantics
var server = "localhost:27017";
var dbName = "platform_asset";
var mongo = new Mongo(server);
var db = mongo.getDB("platform_asset");

// find locked connections
db.$cmd.sys.inprog.find({"waitingForLock":true}).sort({"secs_running":1})

//find all connections not just inprog
db.currentOp( {$all: 1})

// simple js to spool out data
var server = "localhost:27017";
var mongo = new Mongo(server);
var db = mongo.getDB("share_mspmigration");
res = db.PageElement.find({},{lid:1,_id:0}).sort({lid:1})
while (res.hasNext()) printjson(res.next());

// utility to average values in array
Array.prototype.avg = function() {
    var av = 0;
    var cnt = 0;
    var len = this.length;
    for (var i = 0; i < len; i++) {
        var e = +this[i];
        if(!e && this[i] !== 0 && this[i] !== '0') e--;
        if (this[i] == e) {av += e; cnt++;}
}
return av/cnt;
}

Array.prototype.max = function() {
var max = this[0];
var len = this.length;
for (var i = 1; i < len; i++) if (this[i] > max) max = this[i];
return max;
}
Array.prototype.min = function() {
var min = this[0];
var len = this.length;
for (var i = 1; i < len; i++) if (this[i] < min) min = this[i];
return min;
}

getLatency=function(){
    var arr=db.system.profile.find().sort({$natural:-1}).limit(100)
    var res=[]
    for(var i=0; i<arr.length(); i++) {
        res.push(arr[i].millis)
    }
    printjson("Average:"+res.avg()+" Max:"+res.max()+" Min:"+res.min())
}



//db.currentOp().inprog.forEach(
   function(d){
     if(d.waitingForLock && d.lockType != "read") 
       printjson(d)
     })
//Finding Active Write
db.currentOp().inprog.forEach(
   function(d){
     if(d.active && d.lockType == "write") 
       printjson(d)
     })
//Finding Active Reads
db.currentOp().inprog.forEach(
   function(d){
     if(d.active && d.lockType == "read") 
       printjson(d)
     })
     
//tailable cursor
var coll = db.oplog.rs;
var lastTimeStamp = coll.find().sort({ '$natural' : -1 })[0].ts;
 
while(1){
    cursor = coll.find({ ts: { $gt: lastTimeStamp } });
    // tailable
    cursor.addOption( 2 );
    // await data
    cursor.addOption( 32 );
 
    while( cursor.hasNext() ){
        var doc = cursor.next();
        lastTimeStamp = doc.ts;
        printjson( doc );
    }
}
