
"""从N个元素中随机抽取k个元素，但是N不定。每个元素抽取的概率是k/N。

先选中前k个，从k+1到最后一个元素，以1/i (i = k+1, k+2, ... N)的概率选中第i个元素，并且随机替换一个原来选中的元素。

P(G留下)= P(G已经存在)* P(G没有被替换)
        = P(G已经存在)*(1 - P(G被替换))
        = P(G已经存在)*(1 - P(第i个元素要替换某个元素)*P(某个元素是G))
        = (k/i)*( 1 - k/(i+1)*(1/k))
        = (k/i)*( 1 - 1/(i+1))
        = k/(i + 1)
"""

 from random import Random

 def RandomSelect(knum, rand=None):
     selection = None
     k_elems_list = []
     count = 0
     if rand is None:
         rand = Random()
     while True:
         item = yield selection
         if len(k_elems_list) < knum:
             k_elems_list.append(item);
         elif rand.randint(0, count) == 0: # 1/k to select the number.
             index = rand.randint(0, knum-1)
             k_elems_list.pop(index)
             k_elem_list.insert(index, item) # exchange the k elem with random number in the elem list.
         count += 1

 def main():
     rand = Random()
     #for i in xrange(10):
     selector = RandomSelect(rand)
     selector.next()
     selection = None
     for item in xrange(10):
         selection = selector.send(item)
     print 'the selection is'
     print selection
     selector.close()

 if __name__ == '__main__':
     main()

