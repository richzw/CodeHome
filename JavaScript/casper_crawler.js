// EDIT: 2013/10/20
// google has updated its kwt UI, this script doesn't work any more!
// may be I will update this script when I have time to investigate their new Interface.
 
 
// requires
var utils = require('utils');
var casper = require('casper').create()
var casper = require('casper').create({
    verbose: true,
    logLevel: "debug"
});
 
// setup globals 
var email = casper.cli.options['email'] || 'REPLACE THIS EMAIL';
var passwd = casper.cli.options['passwd'] || 'REPLACE THIS PASSWORD';
var keywords = casper.cli.options['keywords'] || 'iphone,cars,kindle';
keywords = keywords.split(',');
 
var kwurl = ''
var result = {}
var kws_list = [];
for (var j=0; j<((keywords.length-1)/50+1); j++) {
    kws_list.push( keywords.slice(j*50, j*50+50) );
}
 
// login & save url 
casper.start('http://adwords.google.com');
 
casper.thenEvaluate(function login(email, passwd) {
    document.querySelector('#Email').setAttribute('value', email);
    document.querySelector('#Passwd').setAttribute('value', passwd);
    document.querySelector('form').submit();
}, {email:email, passwd:passwd});
 
 
casper.waitForSelector(".aw-cues-item", function() {
    kwurl = this.evaluate(function(){
        var search = document.location.search;
        return 'https://adwords.google.com/o/Targeting/Explorer'+search+'&__o=cues&ideaRequestType=KEYWORD_IDEAS';
    })
    //this.open(kwurl);
});
 
// control flows 
function start(kwurl) {
    this.start(kwurl); // we should start a new page, 
                       // don't worry, we are still logged in
                       // ``this.open`` won't work here
    this.waitForSelector("button.gwt-Button", function(){});
}
 
 
function query(kws){
    this.thenEvaluate(function(kws){
        document.querySelector('.sEAB').value = kws.join('\n');
        document.querySelector('button.gwt-Button').click();
    }, {kws:kws});
}
 
function parseresults(){
    this.waitForSelector('#gwt-debug-column-GLOBAL_MONTHLY_SEARCHES-row-0-3', function() {
        var o = this.evaluate(function(){
            var o = {};
            var els = document.querySelectorAll('a.sCM');
            for (var i=0; i<els.length; i++){
                var el = els[i];
                pel = el.parentElement.parentElement.parentElement.parentElement.parentElement;
                o[el.textContent] = [pel.nextSibling.nextSibling.textContent, pel.nextSibling.nextSibling.nextSibling.textContent];
            };
            return o
        });
        for (var k in o){
            result[k] = o[k];
        }
    });
}
 
// recusively call so that it runs sequentially
var current_kws = 0;
function check_kws(){
    if (kws_list[current_kws] && kws_list[current_kws].length>0){
        var kws = kws_list[current_kws];
 
        start.call(this, kwurl);
        query.call(this, kws);
        parseresults.call(this);
 
        current_kws++;
        this.run( check_kws );
    }else{
        this.echo("All done");
        utils.dump(result);
        this.exit()
    }
};
 
casper.run(check_kws)
