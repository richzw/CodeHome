
**Q**:

Let's say I have this dictionary:

`dict = {'a': 100, 'b': 5, 'c': 150, 'd': 60};`

I get the key which has greatest value with this code:

`most_similar = max(dic.iteritems(), key=operator.itemgetter(1))[0]`

it returns `'c'`

But I want to select a random key from top 3 greatest values. According to this dictionary top 3 are:

c
a
d

It should randomly select a key from them. How can I do that?

-------------------------------------------

**A1**:

```python
>>> d = {'a': 100, 'b': 5, 'c': 150, 'd': 60}
>>> from collections import Counter
>>> from random import choice
>>> choice(Counter(d).most_common(3))[0]
'c'
```

**A2**:

```python
>>> import heapq
>>> d = {'a': 100, 'b': 5, 'c': 150, 'd': 60}
>>> largest = heapq.nlargest(3, d, key=d.__getitem__)
>>> largest
['c', 'a', 'd']
>>> import random
>>> random.choice(largest)
'c'
```

**A3**:

```python
>>> import random
>>> d = {'a': 100, 'b': 5, 'c': 150, 'd': 60}
>>> random.choice(sorted(d, reverse=True, key=d.get)[:3])
'c'
```



