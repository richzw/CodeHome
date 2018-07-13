
// https://stackoverflow.com/questions/45384185/what-is-the-difference-between-linearsvc-and-svckernel-linear

LinearSVC and SVC(kernel='linear') yield different results, i. e. metrics score and decision boundaries, because they use different approaches. The toy example below proves it:

```python
from sklearn.datasets import load_iris
from sklearn.svm import LinearSVC, SVC

X, y = load_iris(return_X_y=True)

clf_1 = LinearSVC().fit(X, y)  # possible to state loss='hinge'
clf_2 = SVC(kernel='linear').fit(X, y)

score_1 = clf_1.score(X, y)
score_2 = clf_2.score(X, y)

print('LinearSVC score %s' % score_1)
print('SVC score %s' % score_2)

--------------------------
>>>    0.96666666666666667
>>>    0.98666666666666669
```

The key principles of that difference are the following:

- By default scaling, LinearSVC minimizes the squared hinge loss while SVC minimizes the regular hinge loss. It is possible to manually define a 'hinge' string for loss parameter in LinearSVC.
- LinearSVC uses the One-vs-All (also known as One-vs-Rest) multiclass reduction while SVC uses the One-vs-One multiclass reduction. It is also noted here. Also, for multi-class classification problem SVC fits N * (N - 1) / 2 models where N is the amount of classes. LinearSVC, by contrast, simply fits N models. If the classification problem is binary, then only one model is fit in both scenarios. multi_class and decision_function_shape parameters have nothing in common. The second one is an aggregator that transforms the results of the decision function in a convenient shape of (n_features, n_samples). multi_class is an algorithmic approach to establish a solution.
- The underlying estimators for LinearSVC are liblinear, that do in fact penalize the intercept. SVC uses libsvm estimators that do not. liblinear estimators are optimized for a linear (special) case and thus converge faster on big amounts of data than libsvm. That is why LinearSVC takes less time to solve the problem.

In fact, LinearSVC is not actually linear after the intercept scaling as it was stated in the comments section.
