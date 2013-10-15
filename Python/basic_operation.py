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

6
>>> params = {"server":"mpilgrim", "database":"master", "uid":"sa", "pwd":"secret"}  
>>> ["%s=%s" % (k, v) for k, v in params.items()]  
['server=mpilgrim', 'uid=sa', 'database=master', 'pwd=secret']  
>>> ";".join(["%s=%s" % (k, v) for k, v in params.items()])  
'server=mpilgrim;uid=sa;database=master;pwd=secret' 

>>> a = 'server=mpilgrim;uid=sa;database=master;pwd=secret' 
>>> aa = {}  
>>> for i in a.split(';'):aa[i.split('=',1)[0]] = i.split('=',1)[1]  
...   
>>> aa  
{'pwd': 'secret', 'database': 'master', 'uid': 'sa', 'server': 'mpilgrim'} 
