//find the sum of n in the n numbers,
// EX. 1+2+3+4+5=15 7+8=15,

void findContinousSequence(int n){
  int small = 1;
	int big = 2;
	int middle = (n+1)/2;
	int sum = small + big;

	while (small < middle){
		if (sum == n)
			output(small, big);

		while (sum > n){
			sum -= small;
			small++;

			if (sum == n)
				output(small, big);
		}

		big++;
		sum += big;
	}
}
