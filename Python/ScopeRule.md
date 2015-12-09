
**LEGB** Rule.

**L**, Local — Names assigned in any way within a function (`def` or `lambda`)), and not declared global in that function.

**E**, Enclosing function locals — Name in the local scope of any and all enclosing functions (`def` or `lambda`), from inner to outer.

**G**, Global (module) — Names assigned at the top-level of a module file, or declared global in a def within the file.

**B**, Built-in (Python) — Names preassigned in the built-in names module : `open,range,SyntaxError`,...

```python
global_var1 = []
global_var2 = 1

def func():
    # This is OK: It's just accessing, not rebinding
    global_var1.append(4) 

    # This won't affect global_var2. Instead it creates a new variable
    global_var2 = 2 

    local1 = 4
    def embedded_func():
        # Again, this doen't affect func's local1 variable.  It creates a 
        # new local variable also called local1 instead.
        local1 = 5
        print local1

    embedded_func() # Prints 5
    print local1    # Prints 4
```

```python
x = 5
y = 13
def make_closure():
    x = 42
    y = 911
    def func():
        global x # sees the global value
        print(x, y)
        x += 1

    return func

func = make_closure()
func()      # -> print 5 911
print(x, y) # -> 6 13
```

**nonlocal**: It means "not a global or local variable." So it changes the identifier to refer to an enclosing method's variable

```python
def method():
    def method2():
        # In nested method, reference nonlocal variable.
        nonlocal value
        value = 100

    # Set local.
    value = 10
    method2()

    # Local variable reflects nonlocal change.
    print(value)

# Call method.
method()
```
