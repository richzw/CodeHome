AngularJS Directive Attribute Binding Explanation
=====================================================================

When using directives, you often need to pass parameters to the directive. This can be done in several ways.
The first 3 can be used whether scope is true or false. This is still a WIP, so validate for yourself.

1. Raw Attribute Strings

	```javascript
	<div my-directive="some string" another-param="another string"></div>
	
	var directiveFunction = function(){
		return {
			link: function(scope, element, attributes){
	
				console.log(attributes.myDirective);
				console.log(attributes.anotherParam);
	
			}
		};
	}
	```

2. Observing Interpolated Strings (Also Watches for Changes)

	```javascript
	<div my-directive="{{some string}}" another-param="another string"></div>
	
	var directiveFunction = function(){
		return {
			link: function(scope, element, attributes){
			
				console.log(attributes.myDirective); //literal string "{{some string}}", no interpolation
				console.log(attributes.anotherParam); //literally "another string"
	
				attributes.$observe('myDirective', function(value){
					console.log(value);
				});
	
				attributes.$observe('anotherParam', function(value){
					console.log(value);
				});
	
			}
		};
	}
	```

3. Observing Expression Strings (Also watches for changes)

	```javascript
	<div my-directive="modelObject" another-param="modelObject.obj"></div>
	
	var directiveFunction = function(){
		return {
			link: function(scope, element, attributes){
			
				console.log(attributes.anotherParam); //literally "modelObject.obj"
			
				//modelObject is a scope property of the parent/current scope
				scope.$watch(attributes.myDirective, function(value){
					console.log(value);
				});
				
				//modelObject.obj is also a scope property of the parent/current scope
				scope.$watch(attributes.anotherParam, function (value){
					console.log(value);
				});
				
				//if you tried to use $observe, you would get the literal expression "modelObject" and "modelObject.obj", because there's nothing to interpolate
	
			}
		};
	}
	```

4. Evaluating Object Expressions

	```javascript
	<div my-directive="{ param: 34, param2: 'cool' }" another-param="another string"></div>
	
	var directiveFunction = function(){
		return {
			link: function(scope, element, attributes){
	
				//this is designed for directive configuration if there's a alot of configuration parameters
				//one can combine this with interpolation, if the configuration is a JSON string
				var obj = scope.$eval(attributes.myDirective);
				//can also fallback as a string
				var string = scope.$eval(attributes.anotherParam);
	
				console.log(obj);
				console.log(string);
	
			}
		};
	}
	```

5. Isolate Scope One Way String Binding (Parent changes affect child, child changes does not affect parent)

	```javascript
	<div my-directive="{{some.string}}" another-param="{{another.string}}" string-param="somestring"></div>
	
	var directiveFunction = function(){
		return {
			scope: {
				myDirective: '@',
				anotherParam: '@',
				stringParam: '@'
			},
			link: function(scope, element, attributes){
	
				//the '@' binding automatically interpolates the "{{}}" if they exist in the attributes
				console.log(scope.myDirective); //interpolated string
				console.log(scope.anotherParam); //interpolated string
				console.log(scope.stringParam); //literal string
				
				//IMPORTANT: if scope.some.string was not defined on the parent scope, then '@' interpolates it into an EMPTY string, it is still a STRING type
				//if the DOM attribute was not defined, scope.property would returned undefined

				//if the strings are not yet processed when this directive runs
				//this means they are interpolated, but perhaps the true value has not arrived, such as content from AJAX
				//see: http://stackoverflow.com/a/14907826/582917
				attributes.$observe('myDirective', function(value){
					if(value){
						console.log(value);
					}
				});
				attributes.$observe('anotherParam', function(value){
					if(value){
						console.log(value);
					}
				});

				//the $watch method also works because the '@' binding already does the interpolation
				//see: http://stackoverflow.com/a/12976630/582917 & http://stackoverflow.com/a/17224886/582917
				//this only works because it's in an isolate scope, therefore myDirective is part of the scope
				scope.$watch('myDirective', function(value){
					if(value){
						console.log(value);
					}
				});
				
				//the difference between $observe and $watch in this context, is that $observe reruns the interpolation (from the literal attribute value) and watches the value change, whereas the $watch relies on the '@' interpolation and parent binding and simply watches the value change in this current isolated scope
				//this means if want to react to the value change coming from this directive, you'll need to use $watch, otherwise if you only want to react to parent changes, you may use $observe
				
				//multivalue value watching, only possible with $watch
				//make sure to assign an object outside of the scope
				//if you decide to return an object "return { }", a new object reference would be created
				//inside the watch, and thus trigger another watch, resulting in digest errors
				//MAKE SURE TO DO DEEP WATCH!
				var multiValues = {};
				scope.$watch(function(){
					multiValues.myDirective = scope.myDirective;
					multiValues.anotherParam = scope.anotherParam;
					return multiValues;
				}, function(value){
					if(value){
						console.log(value);
					}
				}, true);
	
			}
		};
	}
	```

6. Isolate Scope Two Way Object Binding (Parent chnages affect child and child changes affect parent)

	```javascript
	<div my-directive="modelObject" another-param="{ thisWill: 'result in digest errors' }"></div>
	
	var directiveFunction = function(){
		return {
			scope: {
				myDirective: '=', //use =? for optionality
				anotherParam: '='
			},
			link: function(scope, element, attributes){
	
				//modelObject needs to be defined on the parent scope or you can use "=?" for optionality
				console.log(scope.myDirective); //this will be the parent/current scope's value, it's not the literal string
				//this will result in digest errors: http://stackoverflow.com/q/13594732/582917
				//so don't use object expressions with '='
				console.log(scope.anotherParam);
				
				//IMPORTANT: if scope.modelObject was not defined on the parent scope, then '=' interpolates it into an UNDEFINED type, this works for child objects as well like scope.modelObject.childObject
				//if the DOM attribute was not defined, scope.property would returned undefined

				//the $watch method works when the model values have not yet been processed by the time this directive runs
				scope.$watch('myDirective', function(value){
					if(value){
						console.log(value);
					}
				});
				
				//$observe is useless here, as there is no interpolation whatsoever, the $watch will react to changes from both parent scope and current scope, furthermore any change to the value here, changes the parent value as well
				
				//=? is required if you want to assign values to the current isolated scope property, but the DOM attribute or parent scope property was never defined, checking if it exists or logging its current value won't result in an error
	
			}
		};
	}
	```

7. Isolate Scope Object & Object Literal Expression Binding

	```javascript
	<div my-directive="{ param: 34, param2: 'cool' }" another-param="parentScopeObject"></div>
	
	var directiveFunction = function(){
		return {
			scope: {
				myDirective: '&',
				anotherParam: '&'
			},
			link: function(scope, element, attributes){
	
				//this will return the actual object from the object expression!
				console.log(scope.myDirective());
				//this will return the actual object from the parent scope, if it exists of course!
				//and no "parentScopeObject" is not a function, it's an object
				console.log(scope.anotherParam());
	
			}
		};
	}
	```

8. Isolate Scope Function Expression Binding

	```javascript
	<div my-directive="parentScopeFunction(funcParam, secondParam)"></div>
	
	var directiveFunction = function(){
		return {
			template: '<button ng-click="myDirective({funcParam: 'blah blah', secondParam: 'blah blah'})">It can be executed from inside the DOM too!</button>',
			scope: {
				myDirective: '&'
			},
			link: function(scope, element, attributes){
			
				//IMPORTANT: if scope.parentScopeFunction was not defined on the parent scope, then '&' interpolates it into a NOOP function, it is still a FUNCTION type
				//if the DOM attribute was not defined, scope.property would also still return a noop function

				//if it's defined as something other than a function, an error occurs!
				
				//parameters passed into the bound function expression must be in the form of an object map
				scope.myDirective(
					{
						funcParam: 'This is the value that is going to be passed in as the funcParam',
						secondParam: 'This is another param!'
					}
				);
	
			}
		};
	}
	```
	
9. Non-Isolate Scope Function Expression Binding

	```javascript
	<div my-directive="parentScopeFunction(funcParam)" another-func="parentScopeFunction2()"></div>
	
	var directiveFunction = function($parse){
		return {
			link: function(scope, element, attributes){

				//see this: 
				//http://stackoverflow.com/questions/17583004/call-an-angularjs-controller-function-from-a-directive-without-isolated-scope
				//http://stackoverflow.com/questions/14858682/angularjs-directive-with-isolate-scope-do-i-really-have-to-call-parent-everyw
				
				//apply and eval
				scope.$apply(function() { 
					scope.$eval(attributes.anotherFunc); 
				});

				//apply only
				scope.$apply(attributes.anotherFunc);
				
				//$parse method, this allows parameters to be passed
				var invoker = $parse(attributes.myDirective);
				invoker(scope, {funcParam: 'example value'});
	
			}
		};
	}
	```
