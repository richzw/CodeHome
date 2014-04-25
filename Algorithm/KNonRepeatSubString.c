
// Suffix Array

#include<stdio.h>
#include<string.h>
#include<algorithm>
#define M 20007
#define MAX 1000010
using namespace std;

int sa[MAX],rank[MAX],height[MAX];
int wa[MAX],wb[MAX],wv[MAX],ws[MAX];
int num[MAX],s[MAX];

int cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b]&&r[a+l]==r[b+l];
}

void get_sa(int *r,int n,int m)//Get function
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++)ws[i]=0;
    for(i=0; i<n; i++)ws[x[i]=r[i]]++;
    for(i=1; i<m; i++)ws[i]+=ws[i-1];
    for(i=n-1; i>=0; i--)sa[--ws[x[i]]]=i;
    for(j=1,p=1; p<n; j*=2,m=p)
    {
        for(p=0,i=n-j; i<n; i++)y[p++]=i;
        for(i=0; i<n; i++)if(sa[i]>=j)y[p++]=sa[i]-j;
        for(i=0; i<n; i++)wv[i]=x[y[i]];
        for(i=0; i<m; i++)ws[i]=0;
        for(i=0; i<n; i++)ws[wv[i]]++;
        for(i=1; i<m; i++)ws[i]+=ws[i-1];
        for(i=n-1; i>=0; i--)sa[--ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
void get_height(int *r,int n)//Get height
{
    int i,j,k=0;
    for(i=1; i<=n; i++) rank[sa[i]]=i; //rank function
    for(i=0; i<n; height[rank[i++]]=k)
        for(k?k--:0,j=sa[rank[i]-1]; r[i+k]==r[j+k]; k++);
}

/*
求不可重叠最长重复字串要比重叠稍微麻烦一点。此题做法是二分求解0到n/2的最优答案，求出之再后判断长度是否大于5。
每次二分的中间长度是mid，然后判断是否存在大于mid的情况，因为长度是mid，而且要求不可重叠，
那么就要判断每个后缀sa值的最大和最小之差是否大于等于mid，因为它们之差就是重复字串的长度，
倘若不大于，肯定重叠了，如果有一组满足此情况，那么这个mid就符合情况。
*/
int solve_no_repeat(int n) //二分求解最长长度  
{  
    int maxx=n/2,minn=0,mid,flag; //maxx代表重复子段最长长度，minn代表重复子段最短长度  
    while(minn<=maxx)//二分求解重复子段最长长度  
    {  
        mid=(maxx+minn)/2;//求中间长度  
        int low=sa[1],high=sa[1];//low和high记录sa的起始和结束位置  
        flag=0;  
        for(int i=2;i<n;i++)  
            if(height[i]<mid){low=sa[i];high=sa[i];} //如果前缀比重复子段长度还要小，low和high重新赋值  
            else  
            {  
                low=min(low,sa[i]);  
                high=max(high,sa[i]);  
                if(high-low>=mid){flag=1;break;} //判断结束位置和起始位置之间的距离是否大于重复子段长度  
            }  
        if(flag)minn=mid+1;  
        else maxx=mid-1;  
    }  
    return maxx>=4?maxx+1:0;  
}  
