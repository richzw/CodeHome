/*This function divides a by greatest divisible 
  power of b*/
int maxDivide(int a, int b)
{
  while (a%b == 0)
   a = a/b; 
  return a;
}   
 
/* Function to check if a number is ugly or not */
int isUgly(int no)
{
  no = maxDivide(no, 2);
  no = maxDivide(no, 3);
  no = maxDivide(no, 5);
   
  return (no == 1)? 1 : 0;
}    
 
/* Function to get the nth ugly number*/
int getNthUglyNo(int n)
{
  int i = 1; 
  int count = 1;   /* ugly number count */
 
  /*Check for all integers untill ugly count 
    becomes n*/
  while (n > count)
  {
    i++;      
    if (isUgly(i))
      count++; 
  }
  return i;
}


/*
Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence 
1, 2, 3, 4, 5, 6, 8, 9, 10, 12, ... 
shows the first 10 ugly numbers. By convention, 1 is included. 
Given the integer n,write a program to find and print the n'th ugly number
*/

int Min(int a, int b, int c) {
    return (a < b ? a : b) < c ? (a < b ? a : b) : c;
}
 
int findNthUglyNum(int n) {
  	assert(n > 0);

  	int* pugly_number = new int[n+1];
	if (pugly_number == NULL)
		return 0;
	
	pugly_number[0] = 1; 
	int two = 0;
	int three = 0;
	int five = 0;
	int last_index = 0;
	int ugly_number = 1;
	
	while(last_index < n) {
		// Get the min value of (2^x)*(3^y)*(5^z)
		pugly_number[++last_index] = Min(pugly_number[two] * 2, pugly_number[three] * 3, pugly_number[five] * 5);
	
		if(pugly_number[two]*2 <= pugly_number[last_index]) two++;	
		if(pugly_number[three]*3 <= pugly_number[last_index]) three++;	
		if(pugly_number[five]*5 <= pugly_number[last_index]) five++;
	}
	ugly_number = pugly_number[n-1];
	copy(pugly_number, pugly_number+n, ostream_iterator<int>(cout, " "));
	
	delete[] pugly_number;
 
  	return ugly_number;
}
