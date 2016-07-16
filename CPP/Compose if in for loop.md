### Question

With almost all code I write, I am often dealing with set reduction problems on collections that ultimately end up with naive "if" 
conditions inside of them. Here's a simple example:

```cpp
for(int i=0; i<myCollection.size(); i++)
{
     if (myCollection[i] == SOMETHING)
     {
           DoStuff();
     }
}
```

### Answer

IMHO it's more straight forward and more readable to use a for loop with an `if` inside it. However, if this is annoying for you, 
you could use a `for_each_if` like the one below:

```cpp
template<typename Iter, typename Pred, typename Op> 
void for_each_if(Iter first, Iter last, Pred p, Op op) {
  while(first != last) {
    if (p(*first)) op(*first);
    ++first;
  }
}
```

Usecase:

```cpp
std::vector<int> v {10, 2, 10, 3};
for_each_if(v.begin(), v.end(), [](int i){ return i > 5; }, [](int &i){ ++i; });
```
