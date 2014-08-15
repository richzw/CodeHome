/*
Given a list A of N integers and we are asked Q queries. Each query is denoted by an integer K, 
for which we need to return the sum of product of all possible sublists having exactly K elements.

Example : Let N = 3 and array be {1,2,3} and let there are 2 queries.
Query 1 : K=1 then answer is 6 as For K=1 possible sublists are {1},{2},{3} so answer is 1+2+3=6.
Query 2 : K=2 then answer is 11 as For K=2 possible sublists are {1,2},{2,3},{3,1} so answer is (1×2)+(2×3)+(3×1)=2+6+3=11.
*/

/*
All calculations are to be done mod 100003; there is no problem, since everything here is algebraic. 
If you expand the factored polynomial

(1 + 1 x) (1 + 2 x) (1 + 3 x)
where each factor corresponds to an input value, then you get

1 + 6 x + 11 x^2 + 6 x^3,
and the answer to a query q is the coefficient of x^q. The naive algorithm is to equivalent to expanding a generalized FOIL
method, which takes exponential time. A better algorithm, with quadratic running time, is to accumulate the factors
one by one, with a loop like
*/

for (int i = degree; i > -1; i--) 
  coefficient[i + 1] += coefficient[i] * x;
//where x is the next value.
