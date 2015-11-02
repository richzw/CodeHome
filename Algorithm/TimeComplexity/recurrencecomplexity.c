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

