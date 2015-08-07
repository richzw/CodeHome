var Promise = require('q');

function printData(d) {
    // process the data in the array here!!!
    console.log(d);
}

function runner(data){
    return Promise.resolve(data).then(printData);
}
function picker(item) {
    return (item = this.next()).done ? Promise.reject(item) : Promise.resolve(item.value[1]);
}

function promiseForOf(arr) {
    return function(iterator) {
        var promised = picker.bind(iterator);
        return function next() {
            return promised().then(runner).then(next);
        }()
    }(arr.entries());
}

// example  
var testArr = [10, 1000, 3000, 6000];
promiseWhile(testArr);
