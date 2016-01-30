 3(list sort)
>>> a = [('2011-03-17', '2.26', 6429600, '0.0'), ('2011-03-16', '2.26', 12036900, '-3.0'), ('2011-03-15', '2.33', 15615500,'-19.1')]  
>>> print a[0][0]  
2011-03-17 
>>> b = sorted(a, key=lambda result: result[1],reverse=True)  
>>> print b  
[('2011-03-15', '2.33', 15615500, '-19.1'), ('2011-03-17', '2.26', 6429600, '0.0'), ('2011-03-16', '2.26', 12036900, '-3.0')]  
>>> c = sorted(a, key=lambda result: result[2],reverse=True)  
>>> print c  
[('2011-03-15', '2.33', 15615500, '-19.1'), ('2011-03-16', '2.26', 12036900, '-3.0'), ('2011-03-17', '2.26', 6429600, '0.0')] 

4(list uniq)
>>> lst= [(1,'sss'),(2,'fsdf'),(1,'sss'),(3,'fd')]  
>>> set(lst)  
set([(2, 'fsdf'), (3, 'fd'), (1, 'sss')])  
>>>  
>>> lst = [1, 1, 3, 4, 4, 5, 6, 7, 6]  
>>> set(lst)  
set([1, 3, 4, 5, 6, 7]) 

5(dict sort)
>>> from operator import itemgetter  
>>> aa = {"a":"1","sss":"2","ffdf":'5',"ffff2":'3'}  
>>> sort_aa = sorted(aa.items(),key=itemgetter(1))  
>>> sort_aa  
[('a', '1'), ('sss', '2'), ('ffff2', '3'), ('ffdf', '5')] 

6 #convert dictionary to string
>>> params = {"server":"mpilgrim", "database":"master", "uid":"sa", "pwd":"secret"}  
>>> ["%s=%s" % (k, v) for k, v in params.items()]  
['server=mpilgrim', 'uid=sa', 'database=master', 'pwd=secret']  
>>> ";".join(["%s=%s" % (k, v) for k, v in params.items()])  
'server=mpilgrim;uid=sa;database=master;pwd=secret' 
#convert string to dictionary
>>> a = 'server=mpilgrim;uid=sa;database=master;pwd=secret' 
>>> aa = {}  
>>> for i in a.split(';'):aa[i.split('=',1)[0]] = i.split('=',1)[1]  
...   
>>> aa  
{'pwd': 'secret', 'database': 'master', 'uid': 'sa', 'server': 'mpilgrim'} 

#('a','b','c','d','e','f') which I want to convert to dictionary having elements like ['a':'b', 'c':'d', 'e':'f'].
>>> dict(zip(t[::2], t[1::2]))
'''
This is called an "extended slice", which is of the form start:stop:step. The first one is ::2, 
so it has the default start (the beginning of the tuple) and stop (the end of the tuple), and a step of 2,
'''

'''
allsets = [set([1, 2, 4]), set([4, 5, 6]), set([4, 5, 7])]
What is a pythonic way to compute the corresponding list of sets of elements having no overlap with other sets?
only = [set([1, 2]), set([6]), set([7])]
'''
import itertools
import collections
element_counts = collections.Counter(itertools.chain.from_iterable(allsets))
all_uniques = {elem for elem, count in element_counts.items() if count == 1}
#                                                     ^ viewitems() in Python 2.7
nondupes = [original & all_uniques for original in allsets]

nondupes = [{elem for elem in original if element_counts[elem] == 1}
            for original in allsets]


#mesh two string together
'''
Input:
    u = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    l = 'abcdefghijklmnopqrstuvwxyz'
Output:
    'AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz'
'''
>>> "".join("".join(item) for item in zip(u, l))
>>> "".join(i + j for i, j in zip(u, l))
>>> "".join(list(chain.from_iterable(zip(u, l))))
res = [''] * len(u) * 2
res[::2] = u
res[1::2] = l
print(''.join(res))


#sum([1,2,3]) should be 6 but sum(['A', 1, 'B', 2, 3]) should also be 6. 
sum(val for val in l1 if isinstance(val, numbers.Number))

val=0
for item in list:
    try:
        val+=int(item)
    except ValueError:
        pass


#将时间对象转换成字符串
>>> import datetime
>>> datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
  '2011-01-20 14:05'
 
#时间大小比较
>>> import time
>>> t1 = time.strptime('2011-01-20 14:05',"%Y-%m-%d %H:%M")
>>> t2 = time.strptime('2011-01-20 16:05',"%Y-%m-%d %H:%M")
>>> t1 > t2
  False
>>> t1 < t2
  True
 
#时间差值计算,计算8小时前的时间
>>> datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
  '2011-01-20 15:02'
>>> (datetime.datetime.now() - datetime.timedelta(hours=8)).strftime("%Y-%m-%d %H:%M")
  '2011-01-20 07:03'
 
#将字符串转换成时间对象
>>> endtime=datetime.datetime.strptime('20100701',"%Y%m%d")
>>> type(endtime)
  <type 'datetime.datetime'>
>>> print endtime
  2010-07-01 00:00:00
 
#将从 1970-01-01 00:00:00 UTC 到现在的秒数，格式化输出   
>>> import time
>>> a = 1302153828
>>> time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(a))
  '2011-04-07 13:23:48'
  
#Bad
# create a concatenated string from 0 to 19 (e.g. "012..1819")
nums = ""
for n in range(20):
  nums += str(n)   # slow and inefficient
print nums
#Good
# create a concatenated string from 0 to 19 (e.g. "012..1819")
nums = []
for n in range(20):
  nums.append(str(n))
print "".join(nums)  # much more efficient
#Best
# create a concatenated string from 0 to 19 (e.g. "012..1819")
nums = [str(n) for n in range(20)]
print "".join(nums)

foo = 'foo'
bar = 'bar'
foobar = foo + bar  # This is good
foo += 'ooo'  # This is bad, instead you should do:
foo = ''.join([foo, 'ooo'])

foo = 'foo'
bar = 'bar'
foobar = '%s%s' % (foo, bar) # It is OK
foobar = '{0}{1}'.format(foo, bar) # It is better
foobar = '{foo}{bar}'.format(foo=foo, bar=bar) # It is best
  
