Ref

http://mlwiki.org/index.php/ROC_Analysis

ROC Curves are used to see how well your classifier can separate positive and negative examples and to identify the best threshold for separating them.

To be able to use the ROC curve, your classifier has to be ranking - that is, it should be able to rank examples such that the ones with higher rank are more likely to be positive. For example, Logistic Regression outputs probabilities, which is a score you can use for ranking.

Drawing ROC curve
------

Given a data set and a ranking classifier:

- order the test examples by the score from the highest to the lowest
- start in (0,0)
- for each example x in the sorted order
  - if x is positive, move 1/pos up
  - if x is negative, move 1/neg right
  
where pos and neg are the fractions of positive and negative examples respectively.

This nice gif-animated picture should illustrate this process clearer

![](https://habrastorage.org/files/267/36b/ff1/26736bff158a4d82893ff85b2022cc5b.gif)

On this graph, the y-axis is true positive rate, and the x-axis is false positive rate. Note the diagonal line - this is the baseline, that can be obtained with a random classifier. The further our ROC curve is above the line, the better.

Area Under ROC
-----

![](https://i.stack.imgur.com/QY5BJ.png)

The area under the ROC Curve (shaded) naturally shows how far the curve from the base line. For the baseline it's 0.5, and for the perfect classifier it's 1.

You can read more about AUC ROC in this question: What does AUC stand for and what is it?

Selecting the Best Threshold
------

I'll outline briefly the process of selecting the best threshold, and more details can be found in the reference.

To select the best threshold you see each point of your ROC curve as a separate classifier. This mini-classifiers uses the score the point got as a boundary between + and - (i.e. it classifies as + all points above the current one)

Depending on the pos/neg fraction in our data set - parallel to the baseline in case of 50%/50% - you build ISO Accuracy Lines and take the one with the best accuracy.

Here's a picture that illustrates that and for details I again invite you to the reference

![](https://i.stack.imgur.com/aVFCa.png)
