/*
A double-square number is an integer X which can be expressed as the sum of two perfect squares. 
For example, 10 is a double-square because 10 = 32 + 12. Your task in this problem is, given X, 
determine the number of ways in which it can be written as the sum of two squares.
*/
int doubleSquare(unsigned int m){
	int total = 0;
	int upper = sqrt((double)m/2);

	for (int i = 0; i <= upper; ++i){
		unsigned int ii = i*i;
		for (int j = i; ; j++){
			unsigned int sum = ii + j*j;
			if (sum == m)
				++total;
			else if (sum > m)
				break;
		}
	}

	return total;
}
// enhancement
//Consider that: M = x2 + y2, and we have y2 = M – x2.
int doubleSquare_v1(unsigned int m) {
	int p = sqrt((double)m / 2.0);
	int total = 0;
	for (int i = 0; i <= p; i++) {
		double j = sqrt((double)m - i*i);
		if (j - (int)j == 0.0)   // might have precision issue, 
			total++;             // can be resolved using |j-(int)j| == delta
	}
	return total;
}
