
[jieba](https://github.com/fxsjy/jieba)

jieba中文分词所使用的算法是基于Trie Tree结构来生成句子中文字所有可能成词的情况，然后使用动态规划（Dynamic programming）来找出最大概率的路径，
这个路径就是基于词频的最大分词结果。对于新词，则使用HMM（hidden Markov Model）模型和Viterbi算法来计算出来。


