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

  // gzip only in staging and production envs
  // Add a far further Expire Header in staging and production envs
  app.configure('staging', function () {
  app.use(express.static(__dirname+'public', {maxAge: 265400}));
    app.use(gzippo.staticGzip(__dirname + '/public'))
    app.enable('view cache')
  });

// Be careful, the data buffer of nodejs, when handling the chinese character
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
