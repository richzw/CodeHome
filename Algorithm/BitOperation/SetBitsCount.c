//Write an efficient program to count number of 1s in binary representation of an integer

//Brian Kernighan’s Algorithm:
int countSetBits(int n){
  unsigned int count = 0;
  while (n){
    n &= (n-1);
    count++;
  }
  
  return count;
}

// look up table

// Hacker's Delight
int BitCount(unsigned int u)
{
     unsigned int uCount;

     uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
     return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}
