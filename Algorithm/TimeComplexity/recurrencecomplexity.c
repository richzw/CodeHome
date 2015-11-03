// version A

int powerA(int x, int n)
{
  if (n == 0)
    return 1;
  if (n == 1)
    return x;
  else
    return x * powerA(x, n - 1);
}

// time complexity: T(n) = T(n-1) + 2
//            result: T(n) = 2n - 1


// version B
int powerB(int x, int n)
{
  if (n == 0)
    return 1;
  if (n == 1)
    return x;
  
  if (n%2 == 0)
    return powerB(x*x, n/2);
  else
    return powerB(x*x, n/2)*x;
}

// time complexity: T(n) = T(n/2) + 3
//          result: T(n) = 3log(n) + 1

 int recursiveFun1(int n)
    {
        if (n <= 0)
        return 1;
    else
        return 1 + recursiveFun1(n-1);
}

/*
T(n) = a + T(n - 1)
where a is some constant.

By induction:

T(n) = n * a + T(0) = n * a + b = O(n)
where a, b are some constant.
*/

int recursiveFun2(int n)
{
    if (n <= 0)
        return 1;
    else
        return 1 + recursiveFun2(n-5);
}
/*
T(n) = a + T(n - 5)
where a is some constant

By induction:

T(n) = ceil(n / 5) * a + T(k) = ceil(n / 5) * a + b = O(n)
where a, b are some constant and k <= 0
*/

int recursiveFun3(int n)
{
    if (n <= 0)
        return 1;
    else
        return 1 + recursiveFun3(n/5);
}
/*
T(n) = a + T(n / 5)
where a is some constant

By induction:

T(n) = a * log5(n) + T(0) = a * log5(n) + b = O(log n)
where a, b are some constant
*/


void recursiveFun4(int n, int m, int o)
{
    if (n <= 0)
    {
        printf("%d, %d\n",m, o);
    }
    else
    {
        recursiveFun4(n-1, m+1, o);
        recursiveFun4(n-1, m, o+1);
    }
}

/*
T(n) = a + 2 * T(n - 1)
where a is some constant

By induction:

T(n) = a + 2a + 4a + ... + 2^n * a + T(0) * 2 ^ n 
     = a * 2^(n+1) - a + b * 2 ^ n
     = (2 * a + b) * 2 ^ n - a
     = O(2 ^ n)
where a, b are some constant.
*/

int recursiveFun5(int n)
{
    for(i=0;i<n;i+=2)
        do something;

    if (n <= 0)
        return 1;
    else
        return 1 + recursiveFun5(n-5);
}
/*
T(n) = n / 2 + T(n - 5)
We can prove by induction that T(5k) >= T(5k - d) where d = 0, 1, 2, 3, 4

Write n = 5m - b (m, b are integer; b = 0, 1, 2, 3, 4), then m = (n + b) / 5:

T(n) = T(5m - b) <= T(5m)
(Actually, to be more rigorous here, a new function T'(n) should be defined such that T'(5r - q) = T(5r) 
where q = 0, 1, 2, 3, 4. We know T(n) <= T'(n) as proven above. When we know that T'(n) is in O(f), 
which means there exist constant a, b so that T'(n) <= a * f(n) + b, we can derive that T(n) <= a * f(n) + b and 
hence T(n) is in O(f). This step is not really necessary, but it is easier to think when you don't have to 
deal with the remainder.)

Expanding T(5m):

T(5m) = 5m / 2 + T(5m - 5) 
      = (5m / 2 + 5 / 2) * m / 2 + T(0) 
      = O(m ^ 2) = O(n ^ 2)
Therefore, T(n) is O(n ^ 2).

*/
