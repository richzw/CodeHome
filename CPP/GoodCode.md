Q: Is there a better way to write code like this:

`if (var == "first case" or var == "second case" or var == "third case" or ...)`

-------------------------------------------

```cpp
#include <algorithm>
#include <initializer_list>
#include <utility>

template <typename T, typename F>
bool any_of_c(const std::initializer_list<T> & il, F && f)
{
    return std::any_of(il.begin(), il.end(), std::forward<F>(f));
}
Usage:

bool b = any_of_c({"abc", "def", "ghi"},
                  [&var](const char * s) { return s == var; });
```

```cpp
template<class T1, class T2>
bool isin(T1&& t1, T2&& t2) {
   return t1 == t2;
}

template<class T1, class T2, class... Ts>
bool isin(T1&& t1 , T2&& t2, T2&&... ts) {
   return t1 == t2 || isin(t1, ts...);
}

std::string my_var = ...; // somewhere in the code
...
bool b = isin(my_var, "fun", "gun", "hun");
```

