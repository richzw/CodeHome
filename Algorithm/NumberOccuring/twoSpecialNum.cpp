//Q
//There is an array of size n (numbers are between 0 and n - 3) and only 2 numbers are repeated.
//Elements are placed randomly in the array.
//E.g. in {2, 3, 6, 1, 5, 4, 0, 3, 5} n=9, and repeated numbers are 3 and 5.

/*
You know that your Array contains every number from 0 to n-3 and the two repeating ones (p & q). 
For simplicity, lets ignore the 0-case for now.

You can calculate the sum and the product over the array, resulting in:
1 + 2 + ... + n-3 + p + q = p + q + (n-3)(n-2)/2

So if you substract (n-3)(n-2)/2 from the sum of the whole array, you get
sum(Array) - (n-3)(n-2)/2 = x = p + q

Now do the same for the product:
1 * 2 * ... * n - 3 * p * q = (n - 3)! * p * q
prod(Array) / (n - 3)! = y = p * q

Your now got these terms:
x = p + q
y = p * q
=> y(p + q) = x(p * q)

If you transform this term, you should be able to calculate p and q
*/
