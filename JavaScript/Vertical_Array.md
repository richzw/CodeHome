    If I have an array of items, such as,

    const array = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 ]
    How can I map it, so that the screen/page renders,

    1     6     11    16
    2     7     12    17
    3     8     13    18
    4     9     14
    5     10    15

Answer:

```javascript
    var array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18],
        chunk = 5,
        result = array.reduce((r, v, i) => {
            (r[i % chunk] = r[i % chunk] || []).push(v);
            return r;
        }, []);


    result.forEach(a => console.log(...a));
```
