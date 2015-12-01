-------------------

- **Is this time complexity actually O(n^2)**

> 
```python
def urlify(string, length):
    '''function replaces single spaces with %20 and removes trailing spaces'''
    counter = 0
    output = ''
    for char in string:
        counter += 1
        if counter > length:
            return output
        elif char == ' ':
            output = output + '%20'
        elif char != ' ':
            output = output + char
    return output
```

> I understand that this is O(n) in terms of scanning through the actual string from left to right. But aren't strings in Python immutable?
If I have a string and I add another string to it with the + operator, doesn't it allocate the necessary space, copy over the original,
and then copy over the appending string?

**Answer**

- [Python Speed > Use the best algorithms and fastest tools.](https://wiki.python.org/moin/PythonSpeed#Use_the_best_algorithms_and_fastest_tools)

String concatenation is best done with `''.join(seq)` which is an `O(n)` process. In contrast, using the `'+'` or `'+='` operators can
result in an `O(n^2)` process because new strings may be built for each intermediate step. The CPython 2.4 interpreter mitigates 
this issue somewhat; however, `''.join(seq)` remains the best practice.

- Another solution 

```python
output = []
    # ... loop thing
    output.append('%20')
    # ...
    output.append(char)
# ...
return ''.join(output)
```

In a nutshell, the append operation is amortized O(1), (although you can make it strong O(1) by pre-allocating the array to the right
size), making the loop O(n).

-------------------------------------------

- **Hash for lambda function in Python**

> 
```python
>>> fn = lambda: 1
>>> hash(fn)
-9223363290690767077
>>> fn = lambda: 1
>>> hash(fn)
8746164008739
>>> fn = lambda: 1
>>> hash(fn)
-9223363290690767077
>>> fn = lambda: 1
>>> hash(fn)
8746164008739
>>> fn = lambda: 1
>>> hash(fn)
-9223363290690767077
```

**Answer**

Two objects are not guaranteed to hash to the same value unless they compare equal [1].

Python functions, including lambdas, don't generally compare equal even if they have identical code [2]:

```python
>>> (lambda: 1) == (lambda: 1)
False
```

This behaviour is due to the fact that function objects don't provide their own equality operator. Instead, 
they inherit the default one that uses the object's identity, i.e. its address. From the documentation:

If no `__cmp__(), __eq__()` or `__ne__()` operation is defined, class instances are compared by object identity (“address”).
Here is what happens in your particular example:

```python
fn = lambda: 1  # New function is allocated at address A and stored in fn.
fn = lambda: 1  # New function is allocated at address B and stored in fn.
                # The function at address A is garbage collected.
fn = lambda: 1  # New function is allocated at address A and stored in fn.
                # The function at address B is garbage collected.
fn = lambda: 1  # New function is allocated at address B and stored in fn.
                # The function at address A is garbage collected.
...
```

Since address A is always hashed to one value, and address B to another, you are seeing hash(fn) alternate between the two values. 
This alternating behaviour is, however, an implementation artefact and could change one day if, for example,
the garbage collector were made to behave slightly differently.

[1] The converse is generally not true: two objects that compare unequal can have the same hash value. This is called a hash collision.

[2] Calling your lambdas and then hashing the result would of course always give the same value since hash(1) is always the same within one program:

```python
>>> (lambda: 1)() == (lambda: 1)()
True
```

