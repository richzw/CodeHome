//
intersection of sorted lists; 给定几个sorted lists，写程序求它们的交集

参考答案。另外一种是用最小堆，堆中存放第几个list和list中的位置，同时一个变量存放当前最大值。每次移动堆中最小list中元素，和之前最大值比较。相等则有共同元素。循环至结束。
