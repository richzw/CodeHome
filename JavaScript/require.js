//Asynchronous Module Definition

<script src="scripts/require.js" data-main="scripts/app.js"></script>

//主要API主要是下面三个函数:
//define– 该函数用户创建模块。每个模块拥有一个唯一的模块ID，它被用于RequireJS的运行时函数，
//define函数是一个全局函数，不需要使用requirejs命名空间.
define(["logger"], function(logger) {        
        return {
             firstName: “John",
             lastName: “Black“,
             sayHello: function () {
                logger.log(‘hello’);
             }
        }
    }
);

//require– 该函数用于读取依赖。同样它是一个全局函数，不需要使用requirejs命名空间.
require(['jquery'], function ($) {
    //jQuery was loaded and can be used now
});

//config– 该函数用于配置RequireJS.
require.config({
    //By default load any module IDs from scripts/app
    baseUrl: 'scripts/app',
    //except, if the module ID starts with "lib"
     paths: {
        lib: '../lib'
    }, 
    // load backbone as a shim
    shim: {
        'backbone': {
            //The underscore script dependency should be loaded before loading backbone.js
            deps: ['underscore'],
            // use the global 'Backbone' as the module name.
            exports: 'Backbone'
        }
    }
});
