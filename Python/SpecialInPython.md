

--------------------------

- **Python does not allow assignments in expressions**

Python wants to clearly separate statements and expressions, so

```python
line = f.readline()
while line:
    #do something with line
    line = f.readline()
```

rather than

```python
while line = f.readline():
    # do something here
```

However, it could be

```python
for line in iter(f.readline, ""):
    # do something with line
```

