
### Question

Suppose we have a string

`std::string str; // some value is assigned`

Could you please tell me the difference between `str.empty()` and `str[0] == '\0'`?

### Answer

**C++11 and beyond**
------

`string_variable[0]` is required to return the `null` character if the string is empty so there is no undefined behavior and the comparison 
will work if the string is truly empty. However you could have a string that starts with a `null` character like `"\0Hi there"` which
will return true even though it is not empty. If you really want to know whether it is empty, use `empty()`.

**Pre-C++11**
------

The difference is that if the string is empty then `string_variable[0]` has undefined behavior, as there is no index `0` unless the 
string is **const-qualified**. If the string is const qualified then it will return a `null` character.

`string_variable.empty()` on the other hand will return true if the string is empty, and false if it is not; the behaviour will not be undefined.

**To sum it all up**
------

`empty()` is meant to check whether the string/container is empty. If that is what you need to know, then you should use it. Not only
does it work on all containers that provide it but it clearly states your intent which means a lot to people reading your code (that includes you).

