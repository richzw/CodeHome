[Source](http://tech.magnetic.com/2015/05/optimize-python-with-closures.html)

- **With Class**

```python
class PageCategoryFilter(object):
    def __init__(self, config):
        self.mode = config["mode"]
        self.categories = config["categories"]

    def filter(self, bid_request):
        if self.mode == "whitelist":
            return bool(
                bid_request["categories"] & self.categories
            )
        else:
            return bool(
                self.categories and not
                bid_request["categories"] & self.categories
            )
```

The **bound method** issue

Specifically, an instance’s methods are access via a descriptor, a Python feature that allows some code to be executed to satisfy 
the results of an attribute access expression. When Python executes the definition of a class, it wraps each function in a descriptor
whose job is to supply the `self` argument. Later, when you access the attribute for the method, Python calls `__get__` on the descriptor, 
and supplies the instance as an argument. This allows the method descriptor to rewrite the call to the underlying function to 
include the `self` argument. 

- **Function**

```python
def page_category_filter(bid_request, config):
    if config["mode"] == "whitelist":
        return bool(
            bid_request["categories"] & config["categories"]
        )
    else:
        return bool(
            config["categories"] and not
            bid_request["categories"] & config["categories"]
        )
```

**The Dictionary Access Problem**

Ordinarily, and algorithmically, yes, dictionaries are quite fast. However, hidden behind those square brackets is quite a bit of work: 
Python must hash the key, apply a bit-mask to the hash, and look for the item in an array that represents the storage for the dictionary.
Edge cases can create collisions which take even longer to resolve

- **Closure**

```python
def make_page_category_filter(config):
    categories = config["categories"]
    mode = config["mode"]
    def page_category_filter(bid_request):
        if mode == "whitelist":
            return bool(bid_request["categories"] & categories)
        else:
            return bool(
                categories and not
                bid_request["categories"] & categories
            )
    return page_category_filter
```


