#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import unicode_literals

import nltk
import re
from nltk.corpus.reader import TaggedCorpusReader
#from nltk.probability import FreqDist

class Classifier:
    def __init__(self, root, keyWords, devRoot):
        self.__root__ = root
        self.__keyWords__ = keyWords
        self.__corpus__ = None
        self.__classifier__ = None
        self.__dev_corpus__ = None
        self.__dev_root__ = devRoot
        
    def initClassifier(self):
        self.__corpus__ = TaggedCorpusReader(self.__root__, '.*\.txt', sep = '#')
        self.__dev_corpus__ = TaggedCorpusReader(self.__dev_root__, '.*\.txt', sep = '#')
    
    def separateSentence(self):
        grammer = r"""
        NP:
            {<.*>+}
            }<PU>{
        """
        return nltk.RegexpParser(grammer)

    def separateParagraphByReg(self, parag):
        '''
        :return: a list of sentences separated by (,|.) in this paragraph 
        :param parag: the paragraph before seggment
        :type parag: string
        '''
        grammer = re.compile('，|。')
        return grammer.split(parag)
        
    def updateFeatures(self, src, dest):
        for key, val in src.items():
            if type(val).__name__ == 'bool' and val:
                dest[key] = val
            elif type(val).__name__ == 'int':
                if key in dest:
                    dest[key] += val
                else:
                    dest[key] = val
    
    def training(self):
        trainSet = []
        for file in self.__corpus__.fileids():
            trainingData = re.match(r"[a-z]+", file)
            if trainingData is None:
                continue      # skip the non training data
            sentences = self.__corpus__.tagged_sents(file)
            features = {}
            for sent in sentences:
                tree = self.separateSentence().parse(sent)
                for subtree in tree.subtrees(lambda t: t.label() == 'NP'):
                    subfea = self.salespersonFeature(list(subtree)) # [(word, tag)]
                    self.updateFeatures(subfea, features)
            print(features)
            trainSet.append((features, re.match(r"[a-z]+", file).group(0)))
        self.__classifier__ = nltk.NaiveBayesClassifier.train(trainSet)
    
    def salespersonFeature(self, sent):
        features = {}
        words = [word for (word, tag) in sent]
        for w in self.__keyWords__:
            features["count(%s)" % w] = words.count(w)
            features["has(%s)" % w] = (w in words)
        return features
        
    def distinguishSalesFromTagfile(self, tagfile):
        sents = self.__corpus__.tagged_sents(tagfile)
        feas = {}
        for sent in sents:
            tree = self.separateSentence().parse(sent)
            for subtree in tree.subtrees(lambda t: t.label() == 'NP'):
                subfea = self.salespersonFeature(list(subtree))
                self.updateFeatures(subfea, feas)
        return self.__classifier__.classify(feas)
    
    def testClassifierAccuracy(self):
        testFea = []
        for file in self.__dev_corpus__.fileids():
            trainingData = re.match(r"[a-z]+", file)
            if trainingData is None:
                continue      # skip the non testing data            
            sentences = self.__dev_corpus__.tagged_sents(file)
            features = {}
            for sent in sentences:
                tree = self.separateSentence().parse(sent)
                for subtree in tree.subtrees(lambda t: t.label() == 'NP'):
                    subfea = self.salespersonFeature(list(subtree))
                    self.updateFeatures(subfea, features)
            testFea.append((features, re.match(r"[a-z]+", file).group(0)))
        return nltk.classify.accuracy(self.__classifier__, testFea)

def main():
    c = Classifier("/Users/zangw/Data/mining/tagnewnn", 
    [u"服务", u"好", u"没有", u"满意", u"态度", u"仔细", u"到位", u"可以", u"行", u"不行", \
    u"不如", u"不好", u"不满意", u"不到位"],
    "/Users/zangw/Data/mining/tag")
    c.initClassifier()
    c.training()
    print(c.testClassifierAccuracy())
    #result = c.distinguishSalesFromTagfile('10000004.txt') 
    #print(result)
    
if __name__ == '__main__':
    main()


