// Source: https://github.com/petkaantonov/bluebird/wiki/Optimization-killers

/*
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



