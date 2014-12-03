var a = [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ];
var b = [ "foo", "bar", "baz", "bam", "bun", "fun" ];

// method 1
var c = a.concat( b );

a; // [1,2,3,4,5,6,7,8,9]
b; // ["foo","bar","baz","bam","bun","fun"]
c; // [1,2,3,4,5,6,7,8,9,"foo","bar","baz","bam","bun","fun"]


// method 2 loop insert
for (var i=0; i < b.length; i++) {
    a.push( b[i] );
}
a; // [1,2,3,4,5,6,7,8,9,"foo","bar","baz","bam","bun","fun"]
b = null;


// method 3 `b` onto `a`:
a = b.reduce( function(coll,item){
    coll.push( item );
    return coll;
}, a );
a; // [1,2,3,4,5,6,7,8,9,"foo","bar","baz","bam","bun","fun"]

// or `a` into `b`:
b = a.reduceRight( function(coll,item){
    coll.unshift( item );
    return coll;
}, b );
b; // [1,2,3,4,5,6,7,8,9,"foo","bar","baz","bam","bun","fun"]

// method 4
// `b` onto `a`:
a.push.apply( a, b );
a; // [1,2,3,4,5,6,7,8,9,"foo","bar","baz","bam","bun","fun"]

// or `a` into `b`:
b.unshift.apply( b, a );
b; // [1,2,3,4,5,6,7,8,9,"foo","bar","baz","bam","bun","fun"]

// about reduce
var total = [0, 1, 2, 3].reduce(function(a, b) {
  return a + b;
});
// total == 6

var flattened = [[0, 1], [2, 3], [4, 5]].reduce(function(a, b) {
  return a.concat(b);
});
// flattened is [0, 1, 2, 3, 4, 5]
