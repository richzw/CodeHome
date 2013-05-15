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
