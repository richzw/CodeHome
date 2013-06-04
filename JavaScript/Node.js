// code about nodejs

process.on('uncaughtException', function (err) {
  error('Caught exception: ' + err);
  if ('trace' in err) {
    err.trace();
  }
  if ('stack' in err) {
    console.log(err.stack);
  }
});
//Attention: the above method is discarded from Node0.8+
// Now use Domain instead of it.
// create a top-level domain for the server
// Ref: http://nodejs.org/api/domain.html
var serverDomain = domain.create();

serverDomain.run(function() {
  // server is created in the scope of serverDomain
  http.createServer(function(req, res) {
    // req and res are also created in the scope of serverDomain
    // however, we'd prefer to have a separate domain for each request.
    // create it first thing, and add req and res to it.
    var reqd = domain.create();
    reqd.add(req);
    reqd.add(res);
    reqd.on('error', function(er) {
      console.error('Error', er, req.url);
      try {
        res.writeHead(500);
        res.end('Error occurred, sorry.');
      } catch (er) {
        console.error('Error sending 500', er, req.url);
      }
    });
  }).listen(1337);
});


  // gzip only in staging and production envs
  // Add a far further Expire Header in staging and production envs
  app.configure('staging', function () {
  app.use(express.static(__dirname+'public', {maxAge: 265400}));
    app.use(gzippo.staticGzip(__dirname + '/public'))
    app.enable('view cache')
  });

// Be careful, the data buffer of nodejs, when handling the chinese character
// http://cnodejs.org/topic/4faf65852e8fb5bc65113403
// http://www.infoq.com/cn/articles/nodejs-about-buffer
var http = require('http');
var $ = require('jquery')
var fs = require('fs');
var iconv = require('iconv-lite');
var BufferHelper = require('bufferhelper');
var url = "http://bbs.nju.edu.cn/bbstcon?board=S_Information&file=M.1367076046.A"
function getFromURL(){
    var html='';
    var req = http.get(url,function(res){
       // res.setEncoding('binary');
        var buffer = new BufferHelper();
        res.on('data',function(data){
            buffer.concat(data);
        }).on('end',function(){
            var buf = buffer.toBuffer();
 
            //var buf = new Buffer(html,'binary');
            var str = iconv.decode(buf,'GBK');
            console.log(str);
        }).on('close',function(){
            console.log('Close recevied!');
        });
    });
    req.on('error',function(error){
        fs.appendFile('error.log',new Date().getTime()+' '
            +error+'\r\n','utf-8');
    });
};
getFromURL()
