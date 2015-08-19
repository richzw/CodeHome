Q: [**given numbers 1..100, find the missing number(s)**](http://stackoverflow.com/questions/3492302/easy-interview-question-got-harder-given-numbers-1-100-find-the-missing-numbe?rq=1)

Remember sum of i-th powers, where i=1,2,..,k. This reduces the problem to solving the system of equations

-  a1 + a2 + ... + ak = b1
-  a12 + a22 + ... + ak2 = b2
-  ...
-  a1k + a2k + ... + akk = bk

Using Newton's identities, knowing bi allows to compute

- c1 = a1 + a2 + ... ak
- c2 = a1a2 + a1a3 + ... + ak-1ak
- ...
- ck = a1a2 ... ak

If you expand the polynomial (x-a1)...(x-ak) the coefficients will be exactly c1, ..., ck - see Viète's formulas. 
Since every polynomial factors uniquely (ring of polynomials is an Euclidean domain), this means ai are uniquely determined,
up to permutation.

This ends a proof that remembering powers is enough to recover the numbers. For constant k, this is a good approach.
High level pseudocode for constant k:

- •	Compute i-th powers of given numbers
- •	Subtract to get sums of i-th powers of unknown numbers. Call the sums bi.
- •	Use Newton's identities to compute coefficients from bi; call them ci. Basically, c1 = b1; c2 = (c1b1 - b2)/2; 
  see Wikipedia for exact formulas
- •	Factor the polynomial xk-c1xk-1 + ... + ck.
- •	The roots of the polynomial are the needed numbers a1, ..., ak.

For varying k, find a prime n <= q < 2n using e.g. Miller-Rabin, and perform the steps with all numbers reduced modulo q.
