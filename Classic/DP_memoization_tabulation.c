a) Memoization (Top Down): The memoized program for a problem is similar to the recursive version 
with a small modification that it looks into a lookup table before computing solutions. 
We initialize a lookup array with all initial values as NIL. Whenever we need solution to a subproblem, 
we first look into the lookup table. If the precomputed value is there then we return that value, 
otherwise we calculate the value and put the result in lookup table so that it can be reused later.

Following is the memoized version for nth Fibonacci Number.

/* Memoized version for nth Fibonacci number */
#include<stdio.h>
#define NIL -1
#define MAX 100
 
int lookup[MAX];
 
/* Function to initialize NIL values in lookup table */
void _initialize()
{
  int i;
  for (i = 0; i < MAX; i++)
    lookup[i] = NIL;
}
 
/* function for nth Fibonacci number */
int fib(int n)
{
   if(lookup[n] == NIL)
   {
    if ( n <= 1 )
      lookup[n] = n;
    else
      lookup[n] = fib(n-1) + fib(n-2);
   }
 
   return lookup[n];
}
 
int main ()
{
  int n = 40;
  _initialize();
  printf("Fibonacci number is %d ", fib(n));
  getchar();
  return 0;
}
b) Tabulation (Bottom Up): The tabulated program for a given problem builds a table in bottom up fashion and 
returns the last entry from table.

/* tabulated version */
#include<stdio.h>
int fib(int n)
{
  int f[n+1];
  int i;
  f[0] = 0;   f[1] = 1; 
  for (i = 2; i <= n; i++)
      f[i] = f[i-1] + f[i-2];
 
  return f[n];
}
  
int main ()
{
  int n = 9;
  printf("Fibonacci number is %d ", fib(n));
  getchar();
  return 0;
}
