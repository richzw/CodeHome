
### Question

`std::string` provides a function `const char* data()` returning a pointer to (since C++11) continous memory.

Now, since the memory is continous and the variable will be destroyed right after the cleanse due to scope end, would it be safe to:

```cpp
char* modifiable = const_cast<char*>(secretString.data());
OpenSSL_cleanse(modifiable, secretString.size());
```

How to cleanse (overwrite with random bytes) `std::string` internal buffer?

### Solution 1

However, since C++11, a `std::string` must be implemented as contiguous data so you can safely access its internal array using the address
of its first element `&secretString[0]`.

```cpp
if(!secretString.empty()) // avoid UB
{
    char* modifiable = &secretString[0];
    OpenSSL_cleanse(modifiable, secretString.size());
}
```

### Solution 2

```cpp
#ifdef WIN32

#pragma optimize("",off)
void trashString(std::string& str){
   std::fill(str.begin(),str.end(),0);
}
#pragma optimize("",on)

#endif

#ifdef __GCC__

void __attribute__((optimize("O0"))) trashString(std::string& str) {
       std::fill(str.begin(),str.end(),0);
}


#endif

#ifdef __clang__

void __attribute__ ((optnone))  trashString(std::string& str) {
       std::fill(str.begin(),str.end(),0);
}

#endif
```


