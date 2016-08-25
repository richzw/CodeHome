[Ref](https://developers.google.com/protocol-buffers/docs/encoding)

Given one message

```
message Test1 {
  required int32 a = 1;
}
```

If you create a `Test1` message and set `a` to `150`, then the encodes message is `08 96 01`.

### Message structure

`key-value` pairs, each key is a `varint` with `(field_number << 3) | wire_type`, in other words, the last three bits of the number store 
the wire type. Thus, `08` (dropping the msb), `000 1000`, 

96 01 = 1001 0110    0000 0001
      -> 000 0001   +   001 0110 (drop the msb and reverse the groups of 7 bits)
      -> 10010110
      -> 2 + 4 + 16 + 128 = 150

### signed integers

`ZigZag` encoding maps singed integers to unsigned integers, so that -1 is encoded as 1, 1 is encoded as 2, -2 is encoded as 3 and so on

```
signed original         Encoded as
----------------------------------
0                          0
-1                         1
1                          2
-2                         3
...
```

### string

```
message Test2 {
  required string b = 2;
}
```

Setting the value of b to 'testing' gives you: `12 07 74 65 73 74 69 6e 67`. `0x12 --> tag = 2, type = 2`. The length varint 
in the value is `7`. The `testing` string is `UTF8`






