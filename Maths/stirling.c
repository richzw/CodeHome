/*
Question:In many applications very large integers numbers are required. 
Some of these applications are using keys for secure transmission of data, encryption, etc.
In this problem you are given a number, you have to determine the number of digits in the factorial of the number.
*/
#define e 2.7182818284590452354
#define pi acos((double)-1)

//log10(n!)=log10(1)+ log10(2) +log10(3)...+log10(n);
int get_factorial_digits(int n){
    double sum;

    sum=1;
    for(int i=1;i<=n;i++)
        sum+=log10((double)i);

    return sum;
}

// strling numbers
//log10(n!)=1.0/2*log10(2*pi*n)+n*log10(n/e)
int get_factorial_digits_strling(int n){
	return (int)(1.0/2.0*log((double)2.0*pi*n)/log(10.0)+1.0*n*log(n/e)/log(10.0)+1);
}
