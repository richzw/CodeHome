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

/*
给出N个房间，每个房间的钥匙随机放在某个房间内，概率相同。有K次炸门的机会，求能进入所有房间的可能性为多大。
*/
// stirling 
/*
钥匙与门的对应关系呈现出环。打开一个门之后，环内的所有房间都可以进入。也就是说N个房间形成1--K个环的可能有多大。
N个房间N个钥匙的总数为N！。之后是求N个房间形成i个环的总数。
题目还有个特殊要求，不能破1号的门。也就是说1号不能独立成环，否则就失败。
第一类斯特林数S（P,K）=(P-1)*S(P-1,K)+S(P-1,K-1)表示的正是N个元素形个K个非空循环排列的方法数。
枚举形成的环，但是要除掉1号独立成环的可能。
S(N,M)-S(N-1,M-1)，N个元素形成 M个环，减去除了1之外的N-1个元素形成M-1个环，也就是1独立成环。
*/
#define eps 1e-7
#define LL long long
using namespace std;
LL fac[21]={1};
LL stir1[21][21];
int main(){
    for(int i=1;i<21;i++)
        fac[i]=fac[i-1]*i;
    for(int i=1;i<=20;i++){
        stir1[i][0]=0;
        stir1[i][i]=1;
       for(int j=1;j<i;j++)
           stir1[i][j]=stir1[i-1][j-1]+(i-1)*stir1[i-1][j];
    }
    int t,n,k;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        if(n==1||k==0){
            printf("0.0000\n");
            continue;
        }
        LL sum=0;
        for(int i=1;i<=k;i++)
            sum+=stir1[n][i]-stir1[n-1][i-1];
        printf("%.4f\n",(double)sum/fac[n]);
    }
    return 0;
}
