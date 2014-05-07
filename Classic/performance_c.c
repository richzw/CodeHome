// stock codes
uint32_t digits10(uint64_t v) {
    uint32_t result = 0;
    do {
        ++result;
         v /= 10;
    } while (v);
     return result;
}

// performance improve
uint32_t digits10(uint64_t v) {
  uint32_t result = 1;
  for (;;) {
    if (v < 10) return result;
    if (v < 100) return result + 1;
    if (v < 1000) return result + 2;
    if (v < 10000) return result + 3;
    // Skip ahead by 4 orders of magnitude
    v /= 10000U;
    result += 4;
  }
}

// better performance
// P01, P02,..., are the respective powers of 10
uint32_t digits10(uint64_t v) {
  if (v < P01) return 1;
  if (v < P02) return 2;
  if (v < P03) return 3;
  if (v < P12) {
    if (v < P08) {
      if (v < P06) {
        if (v < P04) return 4;
        return 5 + (v >= P05);
      }
      return 7 + (v >= P07);
    }
    if (v < P10) {
      return 9 + (v >= P09);
    }
    return 11 + (v >= P11);
  }
  return 12 + digits10(v / P12);
}


// stock codes
uint32_t u64ToAsciiClassic(uint64_t value, char* dst) {
    // Write backwards.
    auto start = dst;
    do {
        *dst++ = ’0’ + (value % 10);
        value /= 10;
    } while (value != 0);
    const uint32_t result = dst - start;
    // Reverse in place.
    for (dst--; dst > start; start++, dst--) {
        std::iter_swap(dst, start);
    }
    return result;
}

// better
uint32_t uint64ToAscii(uint64_t v, char *const buffer) {
    auto const result = digits10(v);
    uint32_t pos = result - 1;
    while (v >= 10) {
        auto const q = v / 10;
        auto const r = static_cast<uint32_t>(v % 10);</uint32_t>
        buffer[pos--] = ’0’ + r;
        v = q;
    }    assert(pos == 0); // Last digit is trivial to handle
    *buffer = static_cast<uint32_t>(v) + ’0’;</uint32_t>
    return result;
} 

// best
unsigned u64ToAsciiTable(uint64_t value, char* dst) {
  static const char digits[201] =
    "0001020304050607080910111213141516171819"
    "2021222324252627282930313233343536373839"
    "4041424344454647484950515253545556575859"
    "6061626364656667686970717273747576777879"
    "8081828384858687888990919293949596979899";
  uint32_t const length = digits10(value);
  uint32_t next = length - 1;
  while (value >= 100) {
    auto const i = (value % 100) * 2;
    value /= 100;
    dst[next] = digits[i + 1];
    dst[next - 1] = digits[i];
    next -= 2;
  }
  // Handle last 1-2 digits
  if (value < 10) {
    dst[next] = '0' + uint32_t(value);
  } else {
    auto i = uint32_t(value) * 2;
    dst[next] = digits[i + 1];
    dst[next - 1] = digits[i];
  }
  return length;
}
