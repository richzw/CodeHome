// Source: https://github.com/petkaantonov/bluebird/wiki/Optimization-killers

/********************************************************************************
 * Tools
*/
//Function that contains the pattern to be inspected (using with statement)
function containsWith() {
    return 3;
    with({}) {}
}

function printStatus(fn) {
    switch(%GetOptimizationStatus(fn)) {
        case 1: console.log("Function is optimized"); break;
        case 2: console.log("Function is not optimized"); break;
        case 3: console.log("Function is always optimized"); break;
        case 4: console.log("Function is never optimized"); break;
        case 6: console.log("Function is maybe deoptimized"); break;
        case 7: console.log("Function is optimized by TurboFan"); break;
        default: console.log("Unknown optimization status"); break;
    }
}

//Fill type-info
containsWith();
// 2 calls are needed to go from uninitialized -> pre-monomorphic -> monomorphic
containsWith();

%OptimizeFunctionOnNextCall(containsWith);
//The next call
containsWith();

//Check
printStatus(containsWith);

// Run the above codes
$ node --trace_opt --trace_deopt --allow-natives-syntax test.js

/********************************************************************************
 * Unsurpported syntex 
*/

// workaround to avoid `try-catch` in production codes

var errorObject = {value: null};
function tryCatch(fn, ctx, args) {
    try {
        return fn.apply(ctx, args);
    }
    catch(e) {
        errorObject.value = e;
        return errorObject;
    }
}

var result = tryCatch(mightThrow, void 0, [1,2,3]);
//Unambiguously tells whether the call threw
if(result === errorObject) {
    var error = errorObject.value;
}
else {
    //result is the returned value
}

/**
 * safe arguments usage
 * 
 * Only use
 *   - arguments.length
 *   - arguments[i] where i is always a valid integer index into the arguments, and cannot be out of bound
 *   - STRICTLY fn.apply(y, arguments)
*/



