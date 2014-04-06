/*
树状数组是一个优美小巧的数据结构，在很多时候可以代替线段树。一句话概括就是，凡是树状数组可以解决的问题，
线段树都可以解决，反过来线段树可以解决的问题，树状数组不一定能解决。

C[i]=a[i-2^k+1]+……+a[i](k为i在二进制形式下末尾0的个数), 
2进制数中从最低位开始连续0的位数的关于2的幂, LowBit(x)= x and -x

LowBit(x)=x and((not x)+1)


*/
// one dimensionality tree array
const int LEN = 10;
int oarr[LEN] = {0};

int lowbit(int t){  //except the parameter 0
	return t&(-t);
}
void update(int idx, int val){
	while (idx < LEN){
		oarr[idx] += val;
		idx += lowbit(idx);
	}
}
int sum_oarr(int n){
	int sum = 0;
	while (n > 0){
		sum += oarr[n];
		n -= lowbit(n);
	}

	return sum;
}

//
// two dimensionality tree array
const int MAX = 1010;  
int carr[MAX][MAX];  
int n;
int Lowbit(int t)  
{  
    return t & (-t);  
}  
void modify(int x, int y, int delta)  
{  
    int i,j;  
    for(i=x; i<=n; i+=Lowbit(i))  
        for(j=y; j<=n; j+=Lowbit(j))  
            carr[i][j] += delta;  
}  
int get_sum(int x,int y)  
{  
    int i,k,sum = 0;  
    for(i=x; i>0; i-=Lowbit(i))  
        for(k=y; k>0; k-=Lowbit(k))  
            sum += carr[i][k];  
    return sum;  
} 
/*
    Sun(1,1)=C[1][1];  Sun(1,2)=C[1][2]; Sun(1,3)=C[1][3]+C[1][2];...
    Sun(2,1)=C[2][1];  Sun(2,2)=C[2][2]; Sun(2,3)=C[2][3]+C[2][2];...
    Sun(3,1)=C[3][1]+C[2][1]; Sun(3,2)=C[3][2]+C[2][2];
*/

