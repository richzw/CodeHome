/*
* Recursive function time complexity
*/

```c
 int recursiveFun1(int n)
    {
        if (n <= 0)
        return 1;
    else
        return 1 + recursiveFun1(n-1);
}

/*
`T(n) = a + T(n - 1)`
where a is some constant.

By induction:

`T(n) = n * a + T(0) = n * a + b = O(n)`
*/

int recursiveFun2(int n)
{
    if (n <= 0)
        return 1;
    else
        return 1 + recursiveFun2(n-5);
}

/*
`T(n) = a + T(n - 5)`
where a is some constant

By induction:

`T(n) = ceil(n / 5) * a + T(k) = ceil(n / 5) * a + b = O(n)`
*/

int recursiveFun3(int n)
{
    if (n <= 0)
        return 1;
    else
        return 1 + recursiveFun3(n/5);
}

/*
`T(n) = a + T(n / 5)`
where a is some constant

By induction:

`T(n) = a * log5(n) + T(0) = a * log5(n) + b = O(log n)`
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
`T(n) = a + 2 * T(n - 1)`
where a is some constant

By induction:

T(n) = a + 2a + 4a + ... + 2^n * a + T(0) * 2 ^ n 
     = a * 2^(n+1) - a + b * 2 ^ n
     = (2 * a + b) * 2 ^ n - a
     = O(2 ^ n)
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

Expanding T(5m):

T(5m) = 5m / 2 + T(5m - 5) 
      = (5m / 2 + 5 / 2) * m / 2 + T(0) 
      = O(m ^ 2) = O(n ^ 2)
      
Therefore, T(n) is O(n ^ 2).
*/
```
