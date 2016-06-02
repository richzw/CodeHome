### Question

Given two integer arrays of same size, “arr[]” and “index[]”, reorder elements in “arr[]” according to given index array.

```
Input:  arr[]   = [50, 40, 70, 60, 90]
        index[] = [3,  0,  4,  1,  2]
Output: arr[]   = [40, 60, 90, 50, 70]
        index[] = [0,  1,  2,  3,   4] 
```

### Solution 1: simple

To use an auxiliary array `temp[]` of same size as given array, tranverse the given array and put all elements at their correct place

```cpp
void reorder(int arr[], int index[], int n)
{
    int temp[n];
 
    // arr[i] should be present at index[i] index
    for (int i=0; i<n; i++)
        temp[index[i]] = arr[i];
 
    // Copy temp[] to arr[]
    for (int i=0; i<n; i++)
    { 
       arr[i]   = temp[i];
       index[i] = i;
    }
}
```

### Solution 2: reorder it inplace

```js
function swap(arr, i, k) {
  var temp = arr[i];
  arr[i] = arr[k];
  arr[k] = temp;
}

function reorder(arr, ind) {
  for (var i = 0, len = arr.length; i < len; i++) {
    if (ind[i] !== i) {
      swap(arr, i, ind[i]);
      swap(ind, i, ind[i]);
    }
  }
}
```

### solution 3: without mutating `index` array

```js
function rearrange(arr, ind) {
    var i, j, buf, temp;
    
    for (j = 0; j < ind.length; j++) {
        if (ind[j] >= 0) { // found a cycle to resolve
            ind[j] = ~ind[j]; // swap all bits, make negative
            i = ~ind[j];
            buf = arr[j];
            while (i !== j) { // not yet back at start of cycle
                // swap buffer with element content
                temp = buf;
                buf = arr[i];
                arr[i] = temp;
                // visit next element in cycle
                ind[i] = ~ind[i];
                i = ~ind[i];
            }
            // dump buffer into final (=first) element of cycle
            arr[j] = buf;
        }
        ind[j] = ~ind[j]; // restore
    }
}
```
