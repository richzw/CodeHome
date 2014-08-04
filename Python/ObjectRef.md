'''python
>>> arr = [[]]*3
>>> id(arr[0]), id(arr[1]), id(arr[2])
(58033672L, 58033672L, 58033672L)
>>> arr[1].append('Py')
>>> arr
[['Py'], ['Py'], ['Py']]
>>> id(arr[0]), id(arr[1]), id(arr[2])
(58033672L, 58033672L, 58033672L)
>>> arr[1].append('Perl')
>>> id(arr[0]), id(arr[1]), id(arr[2])
(58033672L, 58033672L, 58033672L)
>>> arr
[['Py', 'Perl'], ['Py', 'Perl'], ['Py', 'Perl']]
>>> arr[1]=['Go']
>>> id(arr[0]), id(arr[1]), id(arr[2])
(58033672L, 38687240L, 58033672L)
'''

