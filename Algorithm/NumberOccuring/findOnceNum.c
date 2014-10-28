/*
Q: You have an array in which every number is repeated odd number of times (but more than single occurrence). 
Exactly one number appears once. How do you find the number that appears only once?
e.g.: {1, 6, 3, 1, 1, 6, 6, 9, 3, 3, 3, 3}
The answer is 9.

Algorithm:
Here A is the array of length n:
*/
   int ones = 0;  
   int twos = 0;  
   int not_threes, x;  

   for (int i=0; i<n; ++i) {  
            x =  A[i];  
            twos |= ones & x;  
            ones ^= x;  
            not_threes = ~(ones & twos);  
            ones &= not_threes;  
            twos &= not_threes;  
   }  
/*
And the element that occurs precisely once is stored in ones. This uses O(n) time and O(1) space.
I believe I can extend this idea to the general case of the problem, but possibly one of you can do it faster, 
so I'll leave this for now and edit it when and if I can generalize the solution.
Explanation:
If the problem were this: "one element appears once, all others an even number of times", then the solution would be to 
XOR the elements. The reason is that x^x = 0, so all the paired elements would vanish leaving only the lonely element.
If we tried the same tactic here, we would be left with the XOR of distinct elements, which is not what we want.
Instead, the algorithm above does the following:
•	ones is the XOR of all elements that have appeared exactly once so far
•	twos is the XOR of all elements that have appeared exactly twice so far
Each time we take x to be the next element in the array, there are three cases:
1.	if this is the first time x has appeared, it is XORed into ones
2.	if this is the second time x has appeared, it is taken out of ones (by XORing it again) and XORed into twos
3.	if this is the third time x has appeared, it is taken out of ones and twos.
Therefore, in the end, ones will be the XOR of just one element, the lonely element that is not repeated. 
There are 5 lines of code that we need to look at to see why this works: the five after x = A[i].

If this is the first time x has appeared, then ones&x=ones so twos remains unchanged. The line ones ^= x; 
XORs x with ones as claimed. Therefore x is in exactly one of ones and twos, so nothing happens in the last three lines to 
either ones or twos.
If this is the second time x has appeared, then ones already has x (by the explanation above), so now twos gets it 
with the line twos |= ones & x;. Also, since ones has x, the line ones ^= x;removes x from ones (because x^x=0). 
Once again, the last three lines do nothing since exactly one of ones and twos now has x.
If this is the third time x has appeared, then ones does not have x but twos does. So the first line let's twos keep x and
the second adds x to ones. Now, since both ones and twos have x, the last three lines remove x from both.
Generalization:
If some numbers appear 5 times, then this algorithm still works. This is because the 4th time x appears, 
it is in neither ones nor twos. The first two lines then add x to ones and not twos and the last three lines do nothing.
The 5th time x appears, it is in ones but not twos. The first line adds it to twos, the second removed it from ones, 
and the last three lines do nothing.
The problem is that the 6th time x appears, it is taken from ones and twos, so it gets added back to ones on the 7th pass. 
I'm trying to think of a clever way to prevent this, but so far I'm coming up empty.
________________________________________*/
Bit operation
int findUnique(int A[], int size) {
  // First we set up a bit vector and initialize it to 0.
  int count[32];
  for (int j=0;j<32;j++) {
    count[j] = 0;
  }

  // Then we go through each number in the list.
  for (int i=0;i<size;i++) {
    int x = A[i];

    // And for each number we go through its bits one by one.
    for (int j=0;j<32;j++) {
      // We add the bit to the total.
      count[j] += x & 1;
      // And then we take it modulo 3.
      count[j] %= 3;
      x >>= 1;
    }
  }

  // Then we just have to reassemble the answer by putting together any
  // bits which didn't appear a multiple of 3 times.
  int answer = 0;
  for (int j=31;j>=0;j--) {
    answer <<= 1;
    if (count[j] == 1) {
      answer |= 1;
    }
  }

  return answer;
}

