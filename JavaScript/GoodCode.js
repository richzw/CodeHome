// convert arguments into native javascript array
var args = Array.prototype.slice.call(arguments, 0);

//add strim function into String
String.prototype.trim = function () {
	return this.replace(/^\s+|\s+$/g, "");
};

// append one array into another array
var array1 = [12 , "foo" , {name: "Joe"} , -2458]; 
var array2 = ["Doe" , 555 , 100];

Array.prototype.push.apply(array1, array2);

//
function isNumber(n){
	return !isNaN(parseFloat(n)) && isFinite(n);
}

//
function isArray(obj){
	return Object.prototype.toString.call(obj) === '[object Array]';
}

//Get the min and max value of array
var numbers= [5, 458 , 120 , -215 , 228 , 400 , 122205, -85411];
var maxInNumbers = Math.max.apply(Math, numbers);
var minInNumbers = Math.min.apply(Math, numbers);

//clear the array
var myArray = [12, 222, 1000];
myArray.length = 0;

// delete one element of array
var items = [12, 548 ,'a' , 2 , 5478 , 'foo' , 8852, , 'Doe' ,2154 , 119 ];
items.length; // return 11
items.splice(3,1) ;
items.length; // return 10
/* items will be equal to [12, 548, "a", 5478, "foo", 8852, undefined × 1, "Doe", 2154,       119]   */

// use map function to iterate the array
var square = [1, 2, 3, 5].map(function(val){
	return val*val;
});

// avoid for in to iterate the array
var sum = 0;
for (var i = 0, len = arrayNum.length; i < len; ++i){
	sum += arrayNum[i];
}

//1. Failed to save page in web browser
<noscript> <iframe src="*.html"></iframe></noscript>

//2. prevent frame or iframe be contained by others
<script language="javascript">
	if (top.location != self.location)
		top.location = self.location
</script>

//3. Do not alert the script errors
<script language="javascript">
	function killErrors(){
		return true;
	}

	window.onerror = killErrors;
</script>

//4. display the latest update time autumatically
<script language="javascript">
	document.write("The last modify date :" + document.lastModified + "")
</script>
