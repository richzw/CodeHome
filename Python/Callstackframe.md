
### Question

From something like this:

```python
print(get_indentation_level())
    print(get_indentation_level())
        print(get_indentation_level())
```

I would like to get something like this:

```
1
2
3
```

### Answer

If you want indentation in terms of nesting level rather than spaces and tabs, things get tricky. For example, in the following code:

```python
if True:
    print(
get_nesting_level())
```

the call to get_nesting_level is actually nested one level deep, despite the fact that there is no leading whitespace on the line of 
the get_nesting_level call. Meanwhile, in the following code:

```python
print(1,
      2,
      get_nesting_level())
```

the call to get_nesting_level is nested zero levels deep, despite the presence of leading whitespace on its line.

In the following code:

```python
if True:
  if True:
    print(get_nesting_level())

if True:
    print(get_nesting_level())
```

the two calls to get_nesting_level are at different nesting levels, despite the fact that the leading whitespace is identical.

In the following code:

```python
if True: print(get_nesting_level())
```

is that nested zero levels, or one? In terms of INDENT and DEDENT tokens in the formal grammar, it's zero levels deep, but you might not feel the same way.

```python
import inspect
import tokenize

def get_nesting_level():
    caller_frame = inspect.currentframe().f_back
    filename, caller_lineno, _, _, _ = inspect.getframeinfo(caller_frame)
    with open(filename) as f:
        indentation_level = 0
        for token_record in tokenize.generate_tokens(f.readline):
            token_type, _, (token_lineno, _), _, _ = token_record
            if token_lineno > caller_lineno:
                break
            elif token_type == tokenize.INDENT:
                indentation_level += 1
            elif token_type == tokenize.DEDENT:
                indentation_level -= 1
        return indentation_level
```

