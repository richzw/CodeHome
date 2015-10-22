#!/usr/bin/env python
# -*- coding: utf-8 -*-
from __future__ import unicode_literals

'''
This is the word2vector test
'''

import sys
import os
import re
import numpy as np
import logging
from itertools import repeat
from gensim.models import Word2Vec
from sklearn.cluster import KMeans
from sklearn.ensemble import RandomForestClassifier

'''
1. 每一条评论，分词，断句之后，形成paragraph的list，其中包含每个句子的list，句子的list包含的是每个分词。
2. 基于word2vector建立一个汉语的语料modal
3. 采用clustering算法，譬如k-means算法对于modal中的所有词进行cluster
4. 对分类的语句进行词和cluster id的映射
5. 运用机器学习的分类算法adaboost或者其他算法，用第四步的结果进行模型训练
'''

class WordToVec:
	def __init__(self, trainingfilepath, testfilepath):
		self.__train_file_path__ = trainingfilepath
		self.__test_file_path__ = testfilepath
		self.__model__ = None
		self.__isModelSaved__ = False
		self.__model_name__ = 'Word2VecTest'
		self.__forest__ = None
		self.__cluster_idx__ = None
		self.__train__ = None
		self.__test__ = None
		self.__word_index_map__ = None
		self.__cluster_num__ = 0

	def dataToWordList(self, sentencelist, filename):
		# suppose one line in each file
		# remove comma, period
		for sen in sentencelist:
			sen = re.sub("[，|。]", '', sen)
			try:
				sen = sen.encode('utf-8')
			except UnicodeDecodeError as e:
				logging.exception(filename)
			else:
				# split the sentence
				return sen.split()

	def buildWordMap(self, wordlist):
		'''
		'''
		map_num = max(self.__word_index_map__.values()) + 1
		bags = np.zeros(map_num, dtype='float32')
		for word in wordlist:
			if word in self.__word_index_map__:
				index = self.__word_index_map__[word]
				bags[index] += 1
		return bags

	def loadData(self):
		self.__train__ = self.readFile(self.__train_file_path__)
		self.__test__ = self.readFile(self.__test_file_path__)

		return self.__train__, self.__test__

	def listdirforfile(self, path):
		'''
		skip directory and hidden file
		'''
		fnames = os.listdir(path)

		return [f for f in fnames if not os.path.isdir(os.path.join(path, f)) and not f.startswith('.')]

	def readFile(self, filepath):
		if not os.path.exists(filepath):
			return []

		fns = self.listdirforfile(filepath)
		sentences = np.array(zip([0]*len(fns), repeat([], len(fns))), dtype=object)
		for i, fn in enumerate(fns):
			try:
				content = open(os.path.join(filepath, fn))
				# set file content, 
				sentences[i][1] = self.dataToWordList([line for line in content], fn)
				# parse file name as sentiment
				sentences[i][0] = 1 if fn.find('goodsale') != -1 else 0

			except IOError, e:
				logging.exception(e)
		return sentences


	def setW2VModel(self, sentences):
		'''
		set word2vector model

		: param sentences: the traning sentences
		: type sentences: list of list
		'''
		num_features = 300	# word vetor dimensionality
		min_word_count = 2  # Minimum word count
		num_workers = 40	# Number of threads to run in parallel
		context = 10		# Context window size
		downsampling = 1e-3	# downsample setting for frequent words. Why downsampling?

		self.__model__ = Word2Vec(sentences, workers = num_workers, \
							size = num_features, min_count = min_word_count, \
							window = context, sample = downsampling, seed = 1)

		self.__model__.init_sims(replace=True)

		if self.__isModelSaved__:
			self.__model__.save(self.__model_name__)

	def convertTrainData(self, train):
		train_matrix = np.zeros((len(train), self.__cluster_num__), dtype='float32')
		counter = 0
		for sen in train:
			train_matrix[counter] = self.buildWordMap(sen)
			counter += 1
		return train_matrix

	def clusterModelByKMeans(self):
		'''
		Set k (cluster number) to be 1/5th of the vocabulary size,
		average of 5 words per cluster. Just for test

		'''
		word_vec = self.__model__.syn0
		self.__cluster_num__ = word_vec.shape[0] / 3

		# running k means
		kmean_cluster = KMeans(n_clusters = self.__cluster_num__)
		self.__cluster_idx__ = kmean_cluster.fit_predict(word_vec)

		# create word/index map
		self.__word_index_map__ = dict(zip(self.__model__.index2word , self.__cluster_idx__))


	def setTrainingModelByRandomForrest(self, trainData, trainFea):
		'''
		Fit a random forest to the traning set

		：param trainData: traning data vector
		'''
		# Fit a random forest to the training data by using 100 trees
		self.__forest__ = RandomForestClassifier(n_estimators = 100)
		self.__forest__ = self.__forest__.fit(trainData, trainFea) 

	def predictData(self, testdata):
		return self.__forest__.predict(testdata)

'''
Sentence Test class
'''
class MySentence:
	'''
	>>> sentences = MySentence('/somedirectory/')
	>>> model = gensim.models.Word2Vec(sentences)
	'''
	def __init__(self, dirname):
		self.__dirname__ = dirname

	def __iter__(self):
		# os.path.exists(filepath):
		for fname in os.listdir(self.__dirname__):
			for line in open(os.path.join(self.__dirname, fname)):
				# remove comma, period
				line = re.sub("[，|。]", '', line)
				yield line.split()

def main():
	# set utf-8 encoding 
	reload(sys)
	sys.setdefaultencoding('utf-8')

	w = WordToVec('/Users/zangw/Documents/code/mining/train', '/Users/zangw/Documents/code/mining/test')
	trainData, testData = w.loadData()

	# get the traning data
	trainSentences = []
	trainFeatures = []
	for idx in range(len(trainData)):
		trainSentences.append(trainData[idx][1])
		trainFeatures.append(trainData[idx][0])

	print testData[0][1]

	w.setW2VModel(trainSentences)
	w.clusterModelByKMeans()
	w.setTrainingModelByRandomForrest(w.convertTrainData(trainSentences), trainFeatures)

	ret = w.predictData(w.convertTrainData(testData[0][1]))
	print ret

if __name__ == '__main__':
    main()
