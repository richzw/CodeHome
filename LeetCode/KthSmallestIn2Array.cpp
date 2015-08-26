
/*
Given two sorted arrays A, B of size m and n respectively. 
Find the k-th smallest element in the union of A and B. You can assume that there are no duplicate elements.
*/

/***********************************************************************************
  *The trivial way, O(m+n):
Merge both arrays and the k-th smallest element could be accessed directly. Merging would require extra space of O(m+n). 
The linear run time is pretty good, but could we improve it even further?

  *A better way, O(k):
There is an improvement from the above method, Using two pointers, you can traverse both arrays without actually merging them, 
thus without the extra space. 
 
  *The best solution, but non-trivial, O(lg m + lg n):
We try to approach this tricky problem by comparing middle elements of A and B, which we identify as Ai and Bj. 
If Ai is between Bj and Bj-1, we have just found the i+j+1 smallest element. Why? 
Therefore, if we choose i and j such that i+j = k-1, we are able to find the k-th smallest element.   
*/

int findKthSmallest(int A[], int m, int B[], int n, int k) {
  // some asserts for edge condition.
  
  int i = (int)((double)m/(m+n)*(k-1));
  int j = (k-1) - i;
  // invariant: i + j = k-1
  
  Ai_1 = (i == 0)? INT_MIN: A[i-1];
  Bj_1 = (j == 0)? INT_MIN: B[j-1];
  Ai = (i == m)? INT_MAX: A[i];
  Bj = (j == n)? INT_MAX: B[j];
  
  if (Ai < Bj && Ai > Bj_1)
    return Ai;
  if (Bj < Ai && Bj > Ai_1)
    return Bj;
  
  if (Ai < Bj)
    // exclude Ai and the below position
    // exclude Bj and the above position
    return findKthSmallest(A+i+1, m-i-1, B, j, k-i-1);
  else
    return findKthSmallest(A, i, B+j+1, n-j-1, k-j-1);
}
