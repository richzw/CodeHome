/*
Given a function which generates a random integer in the range 1 to 7, 
write a function which generates a random integer in the range 1 to 10 uniformly.
*/
/*
Obviously, we have to run rand7() function at least twice, as there are not enough numbers in the range of 1 to 10. By running rand7() twice, 
we can get integers from 1 to 49 uniformly. Why?

   1  2  3  4  5  6  7
1  1  2  3  4  5  6  7
2  8  9 10  1  2  3  4
3  5  6  7  8  9 10  1
4  2  3  4  5  6  7  8
5  9 10  1  2  3  4  5
6  6  7  8  9 10  *  *
7  *  *  *  *  *  *  *

A table is used to illustrate the concept of rejection sampling.
Calling rand7() twice will get us row and column index that corresponds to a unique position in the table above. 
Imagine that you are choosing a number randomly from the table above. If you hit a number, you return that number immediately. 
If you hit a *, you repeat the process again until you hit a number.
Since 49 is not a multiple of tens, we have to use rejection sampling. Our desired range is integers from 1 to 40, 
which we can return the answer immediately. If not (the integer falls between 41 to 49), we reject it and repeat the whole process again.
*/
int rand7() {
	return rand() % 7;
}

int rand10(){
	int row, col, idx;

	do {
		row = rand7();
		col = rand7();
		idx = col + (row-1)*7;
	}while (idx > 40);

	return 1+(idx-1)%10;
}
