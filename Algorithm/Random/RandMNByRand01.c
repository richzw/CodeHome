/*
Describe an implementation of the procedure RANDOM(a,b) that only makes calls to RANDOM(0,1). 
What is the expected running time of your procedure as a function of a and b?
*/

/*
Let n=b−a. The algorithm is as follows:

We find the smallest integer c such that 2c≥n (c=⌈lnn⌉)
We call RANDOM(0, 1) c times to and get a c-digit binary number r
If r>n we go back to the previous step
Otherwise we return a+r
*/

int rand01(){
	return true;
}

int highestbit(unsigned int n) {
    n |= (n >>  1);
    n |= (n >>  2);
    n |= (n >>  4);
    n |= (n >>  8);
    n |= (n >> 16);
    return n - (n >> 1);
}

// Get random n~m through random 0~1
int generateRandNumberFromNtoM(int n, int m){
	int diff = (m > n)? (m-n):(n-m);

	int bit_count = highestbit(diff);
	
	int r = 0;
	for (int i = 0; i < bit_count; ++i){
		if (rand01())
			r += 1<<i;

		if ((i == bit_count-1) && r > diff){ // continue to generate random number
			r = 0;
			i = 0;
		}
	}

	return (m>n)?(n+r):(m+r);
}
