x if c else y  # note order

#In Python <2.5, use (if you must) one of
 
  c and x or y   # incorrectly returns y if x is (any kind of) false
  (c and [x] or [y])[0]  # reliable, but ugly and churns objects
  (x, y)[not c]  # always evaluates both
  (y, x)[c]      # only if c is really a bool (or otherwise 0 or 1)
