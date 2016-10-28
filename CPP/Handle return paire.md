### Question

C++11 has function `std::minmax_element` which returns a pair of values. This, however, is quite confusing to handle and read, 
and produces an extra, later useless variable to pollute the scope.

```cpp
auto lhsMinmax = std::minmax_element(lhs.begin(), lhs.end());
int &lhsMin = *(lhsMinMax.first);
int &lhsMax = *(lhsMinmax.second);
```

Is there a better way to do this? Something like:

```cpp
int lhsMin;
int lhsMax;
std::make_pair<int&, int&>(lhsMin, lhsMax).swap(
    std::minmax_element(lhs.begin(), lhs.end()));
```

### Answer

`auto [lhsMinIt, lhsMaxIt] = std::minmax_element(lhs.begin(), lhs.end());`
