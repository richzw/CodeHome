/*
 Given an array with N keys, design an algorithm to find all values that occur more than N/10 times. 
 The expected running time of your algorithm should be linear.
*/

/*
Remember up to three elements, together with counters.

1. remember first element, set count1 = 1
2. scan until you find first different element, increasing count1 for each occurrence of element 1
3. remember second elemt, set count2 = 1
4. scan until you find first element different from elem1 and elem2, incrementing count1 or count2, 
 depending which element you see
5. remember third element, set count3 = 1
6. continue scanning, if the element is one of the remembered, increment its count, if it's none of the remembered, 
decrement all three counts; if a count drops to 0, forget the element, go to step 1, 3, or 5, 
depending on how many elements you forget
7. If you have three elements occurring strictly more than one-fourth times the number of elements in the array, 
you will end up with three remembered elements each with positive count, these are the three majority elements.

Small constant additional space, O(n), no sorting.

*/
