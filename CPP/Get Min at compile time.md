### Question

Let's say I have an array of integers defined like that:

`static const int IntArray[] = {1, 5, 10, 12, 17};`

### Answer

Let's get the C++17 solution out of the way for future search-landers:

```cpp
constexpr int IntArray[] = {1, 5, 10, 12, 17};
constexpr int min = *std::min_element(std::begin(IntArray), std::end(IntArray));
static_assert(min == 1);
```

C++11 is more picky with constexpr functions, so we have to roll out a recursive algorithm. This one is a simple, linear one:

```cpp
template <class T>
constexpr T &constexpr_min(T &a, T &b) {
    return a > b ? b : a;
}

template <class T>
constexpr T &arrayMin_impl(T *begin, T *end) {
    return begin + 1 == end
        ? *begin
        : constexpr_min(*begin, arrayMin_impl(begin + 1, end));
}

template <class T, std::size_t N>
constexpr T &arrayMin(T(&arr)[N]) {
    return arrayMin_impl(arr, arr + N);
}

constexpr int IntArray[] = {1, 5, 10, 12, 17};
constexpr int min = arrayMin(IntArray);
```
