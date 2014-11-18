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
