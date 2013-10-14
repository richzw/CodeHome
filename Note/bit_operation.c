//计算n+1
 -~n
//计算n-1
~-n

//取相反数
~n + 1;

//另一种写法
(n ^ -1) + 1;

if(x == a) x = b; if(x == b) x = a;  
  ==>  x = a ^ b ^ x;

//sign函数，参数为n，当n>0时候返回1，n<0时返回-1，n=0时返回0
return !!n – (((unsigned)n >> 31) << 1);

int abs(int n){
	return (n^(n >> 31)) - (n >> 31);
	/* n>>31 取得n的符号，若n为正数，n>>31等于0，若n为负数，n>>31等于-1
若n为正数 n^0=0,数不变，若n为负数有n^-1 需要计算n和-1的补码，然后进行异或运算，
结果n变号并且为n的绝对值减1，再减去-1就是绝对值 */
}
int max(int x, int y){
	return x^((x^y) &-(x<y));
	 /*如果x<y x<y返回1，否则返回0，与0做与运算结果为0，与-1做与运算结果不变*/
}
int min(int x, int y){
	return y^((x^y) & -(x<y));
}
bool isFactorialofTwo(int n){
	return n>0?(n&(n-1) == 0): false;
}
int getAverage(int x, int y){
	return ((x^y) >> 1)+(x&y);
    /*(x^y) >> 1得到x，y其中一个为1的位并除以2，
       x&y得到x，y都为1的部分，加一起就是平均数了*/  
}
