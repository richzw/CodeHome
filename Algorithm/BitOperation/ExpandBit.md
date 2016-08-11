### Question

convert a `uint16_t` input to a `uint32_t` bit mask. One bit in the input toggles two bits in the output bit mask. 

```
Input    Output
ABCDb -> AABB CCDDb
```

### Answer

Refer to [Bit Twiddling](http://graphics.stanford.edu/~seander/bithacks.html#InterleaveBMN)

```c
uint32_t expand_bits(uint16_t bits)
{
    uint32_t x = bits;

    x = (x | (x << 8)) & 0x00FF00FF;
    x = (x | (x << 4)) & 0x0F0F0F0F;
    x = (x | (x << 2)) & 0x33333333;
    x = (x | (x << 1)) & 0x55555555;

    return x | (x << 1);
}
```

Or

```c

```
