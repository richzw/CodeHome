/*
Q:从一个长字符串中查找包含给定字符集合的最短子串。例如，长串为“aaaaaaaaaacbebbbbbdddddddcccccc”，字符集为{abcd}，
那么最短子串是“acbebbbbbd”。如果将条件改为“包含且只包含给定字符集合”，你的算法和实现又将如何改动
*/

/*
我们在分析完之后，提到还可以利用hashmap来实现。这样可以进一步的减小时间复杂度。具体的思路与上期的方法也类似，
只是在判断是否出现的时候，不是采用排序的方法，而是hashmap的方法。具体方法如下：
	1. 遍历一边字符集合，将集合中的字符都加到hashmap中
	2. 然后遍历长串，记录遍历开始pBegin和结束pEnd的位置，直到hashmap中的字符都出现过，则不断移动pBegin，
	查看是否能够满足所有字符集和中的字符都出现了，如果出现：则不断更新最小长度；
	如果没有出现，则停止移动pBegin，开始移动pEnd。依次类推，像一个可以伸缩的窗口在长串上遍历。
*/

int nTargetLen = N + 1;
int pBegin = 0;
int pEnd = 0;
int nLen = N;
int nAbstractBegin = 0;
int nAbstractEnd = 0;

while (true){
  while (!isAllExisted() && pEnd < nLen)
    pEnd++;
    
  while(isAllExisted())
  {
    if (pEnd - pBegin < nTargetLen)
    {
      nTargetLen = pEnd - pBegin;
      nAbstractBegin = pBegin;
      nAbstractEnd = pEnd - 1;
    }
    pBegin++;
  }
  
  if (pEnd >= N)
    break;
}
