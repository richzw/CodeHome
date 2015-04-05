'''
Joseph Ring
'''

def fun1(n, m):
  """
  @param n: totol people number
  @param m: interval number
  """
  lst = range(1, n+1)
  while len(lst) > 0:
    for i in range(m - 1):
      lst.append(lst.pop(0))
    print lst.pop(0)
    
    
def fun2(n, m):
  j = 0
  for i in range(2, n+1):
    j = (j + 1)%i
    
  print j + 1
  
