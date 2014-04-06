/*
Given an N*N matrix A, whose elements are either 0 or 1. A[i, j] means the number in the i-th row and j-th column. 
Initially we have A[i, j] = 0 (1 <= i, j <= N).
We can change the matrix in the following way. Given a rectangle whose upper-left corner is (x1, y1) 
and lower-right corner is (x2, y2), we change all the elements in the rectangle by using "not" operation 
(if it is a '0' then change it into '1' otherwise change it into '0'). To maintain the information of the matrix, 
you are asked to write a program to receive and execute two kinds of instructions.

1. C x1 y1 x2 y2 (1 <= x1 <= x2 <= n, 1 <= y1 <= y2 <= n) changes the matrix by using the rectangle 
  whose upper-left corner is (x1, y1) and lower-right corner is (x2, y2).
2. Q x y (1 <= x, y <= n) querys A[x, y]. 
*/

//http://blog.csdn.net/zxy_snow/article/details/6264135
//

// solution: two dimemsionality tree array
const int MAX = 1010;  
int c[MAX][MAX];  
int n;  
int Lowbit(int x)  
{  
    return x & (-x);  
}  
void Updata(int x,int y)  
{  
    int i,k;  
    for(i=x; i<=n; i+=Lowbit(i))  
        for(k=y; k<=n; k+=Lowbit(k))  
            c[i][k]++;  
}  
int Get(int x,int y)  
{  
    int i,k,sum = 0;  
    for(i=x; i>0; i-=Lowbit(i))  
        for(k=y; k>0; k-=Lowbit(k))  
            sum += c[i][k];  
    return sum;  
}  
int main()  
{  
    int ncases,m;  
    int x1,y1,x2,y2;  
    char ch[2];  
    scanf("%d",&ncases);  
    while( ncases-- )  
    {  
        memset(c,0,sizeof(c));  
        scanf("%d%d",&n,&m);  
        while( m-- )  
        {  
            scanf("%s",ch);  
            if( ch[0] == 'C' )  
            {  
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);  
                x1++; y1++; x2++; y2++;  
                Updata(x2,y2);  
                Updata(x1-1,y1-1);  
                Updata(x1-1,y2);  
                Updata(x2,y1-1);  
            }  
            else  
            {  
                scanf("%d%d",&x1,&y1);  
                printf("%d/n",Get(x1,y1)%2);  
            }  
        }  
        printf("/n");  
    }  
return 0;  
}  
