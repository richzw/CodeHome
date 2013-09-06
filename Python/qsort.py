
def qsort(l): 
     return l if len(l)<=1 else qsort([x for x in l[1:] if x<l[0]]) + [l[0]] + qsort([x for x in l[1:] if x>=l[0]])
