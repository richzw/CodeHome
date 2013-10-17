window.onload = function() {
 
    setTimeout(function() {
// reference to <head>
        var head = document.getElementsByTagName('head')[0];

// a new CSS
        var css = document.createElement('link');
        css.type = "text/css";
        css.rel  = "stylesheet";
        css.href = "http://domain.tld/preload.css";
 
// a new JS
        var js  = document.createElement("script");
        js.type = "text/javascript";
        js.src  = "http://domain.tld/preload.js";
 
// preload JS and CSS
        head.appendChild(css);
        head.appendChild(js);
 
// preload image
        new Image().src = "http://domain.tld/preload.png";
 
    }, 1000);
};

/////////////////////////////////////////////////////////////////////////
function preloader() {
    if (document.images) {
        var img1 = new Image();
        var img2 = new Image();
        var img3 = new Image();
        img1.src = "http://domain.tld/path/to/image-001.gif";
        img2.src = "http://domain.tld/path/to/image-002.gif";
        img3.src = "http://domain.tld/path/to/image-003.gif";
    }
}
function addLoadEvent(func) {
    var oldonload = window.onload;
    if (typeof window.onload != 'function') {
        window.onload = func;
    } else {
        window.onload = function() {
            if (oldonload) {
                oldonload();
            }
            func();
        }
    }
}
addLoadEvent(preloader);

/////////////////////////////////////////////////////////////////////////////
function preloader() {
    if (document.getElementById) {
        document.getElementById("preload-01").style.background = "url(http://domain.tld/image-01.png) no-repeat -9999px -9999px";
        document.getElementById("preload-02").style.background = "url(http://domain.tld/image-02.png) no-repeat -9999px -9999px";
        document.getElementById("preload-03").style.background = "url(http://domain.tld/image-03.png) no-repeat -9999px -9999px";
    }
}
function addLoadEvent(func) {
    var oldonload = window.onload;
    if (typeof window.onload != 'function') {
        window.onload = func;
    } else {
        window.onload = function() {
            if (oldonload) {
                oldonload();
            }
            func();
        }
    }
}
addLoadEvent(preloader);
