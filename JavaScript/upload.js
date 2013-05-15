module.exports = function(app){
  	var fs = require('fs')
		, gfs = require('../../lib/gridfs')
		, path = require('path')
		, async = require('async')
		, im = require('imagemagick');	

	app.get('/upload/new', function(req, res){
		res.render('upload/index');
	});

	app.del('/upload/:fileid', function(req, res, next){
		gfs.deleteGridFile(req.params.fileid, function(err){
			if (err){ 
				next(err);
			}else{
				console.log('Dear, the GridFile '+req.params.fileid+' is deleted successfully!!!');
				res.redirect('back');
			}
		});
	});

	app.get('/upload/:fileid', function(req, res, next){
		gfs.getGridFile(req.params.fileid, function(err, file){
			if (err) return next(err);

			res.header('Content-Type', file.contentType);
			res.header('Content-Disposition', 'attachment; filename='+file.filename);
			return file.stream(true).pipe(res);
		});
	});

	app.post('/upload/create', auth.loadUser, function(req, res, next){
		//save the upload file to folder public/doc/	
		var tmppath = req.files.file.path;
		var tmpname = req.files.file.name;
		var sourcepath = path.resolve(__dirname, '../../', './public/images/' + tmpname);
		var targetpath = path.resolve(__dirname, '../../', './public/images/');
		var targetname = targetpath + '/small' + tmpname;
		var picturename = 'small'+tmpname;
		var bigtargetname = targetpath + '/big' + tmpname;
		var bigpicturename = 'big'+tmpname;
		var filetype = req.files.file.type;

		console.log(process.platform);
		if(process.platform.match(/^win/) != null){
			im.convert.path = 'C:/Program Files/ImageMagick-6.8.0-Q16/convert.exe';
			im.identify.path = 'C:/Program Files/ImageMagick-6.8.0-Q16/identify.exe';
		}
		var opts = {content_type : filetype};
		async.series({
			movePic: function (callback) {
				//move picture to public/images/
				fs.rename(tmppath, sourcepath, function (err) {
					if (err)
						callback(err);
					else
						callback();
				});
			},
			resizeSmallPic: function (callback) {
				//resize to the small picture
				im.resize({ srcPath: sourcepath,
							dstPath: targetname,
							format: filetype,
							strip: false,
							width: picture_config.smallpicturewidth,
							height: picture_config.smallpictureheight
							}, function (err, stdout, stderr) {
								if (err)
									callback(err);
								else
									callback();
							});
			},
			saveSmallPic: function(callback){
				//save the small picture to mongoDB
				gfs.putGridFileByPath(targetname, picturename, opts, function(err, result){
					if (err)
						callback(err);
					else
						callback(null, result._id);
				});
			},
			resizeBigPic: function (callback) {
				//resize to the big picture
				im.resize({ srcPath: sourcepath,
							dstPath: bigtargetname,
							format: filetype,
							strip: false,
							width: picture_config.bigpicturewidth,
							height: picture_config.bigpictureheight
							}, function (err, stdout, stderr) {
								if (err)
									callback(err);
								else
									callback();
							});
			},
			saveBigPic: function (callback) {
				//save the big picture
				gfs.putGridFileByPath(bigtargetname, bigpicturename, opts, function (err, result) {
					if (err)
						callback(err);
					else
						callback(null, result._id);
				});
			},
		}, function (err, results) {
			if (err){
				 next(err);
			}else{
					var user = req.currentUser;
					if (user.hasAvatar) {
						//delete the old avatar
						if (user.small_avatar_id) {
								gfs.deleteGridFile(user.small_avatar_id, function (err) {
										if (err)
											next(err);
									console.log('Dear, the GridFile '+user.small_avatar_id+' is deleted successfully!!!');
								});
						}
						if (user.big_avatar_id) {
								gfs.deleteGridFile(user.big_avatar_id, function(err){
										if (err)
											next(err);
									console.log('Dear, the GridFile '+user.big_avatar_id+' is deleted successfully!!!');
								});
						}
					}
					//save the user information
					user.hasAvatar = true;
					user.small_avatar_id = results.saveSmallPic;
					user.big_avatar_id = results.saveBigPic;
					user.save(function (err) {
						if (err)
							next(err);
						else
							res.send({id: results.saveBigPic});
					});
			}
		});
	});
	
	app.put('/tasks/assign/:taskIdStr', auth.loadUser, function (req, res, next) {
		//handle ajax request
		//var user = req.currentUser;
		var email = req.body.member.toString().replace(' ', '.')+"@igt.com";

		Task
			.findAndModify(req.params.taskIdStr,
					[],
					{
						$set: {
							owner: req.body.member,
							iteration: req.body.iterations
						}
					},
					{ upsert: true },
					function (err, result) {
						if (err)
							next(err);
						else {
							// send browser notification to assigned user
							_.filter(user_socket_map, function(elem) { 
								if (elem.name === req.body.member){
									user_socket_map[i].socket.emit('notifytask', { task: result });
								}
							});

							sendAssignTaskEmail(email, req.body.member);
							res.send(200);
						}

			});
	});	
}
