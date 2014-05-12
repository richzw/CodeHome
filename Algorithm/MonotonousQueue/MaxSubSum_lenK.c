/*
求长度不超过k的连续最大子段和。

    设dp[i]表示以i结尾的满足约束的最大子段和，sum[i]表示从0到第i个数的和，状态转移方程：dp[i]=sum[i]-min{sum[j]},i-k<=j<i，
    最后结果为max(dp[i]).直接二重循环超时。设b[i]=i-k，b[i]随i的增长单调不降，可以考虑用单调队列优化。构造一个单调递减队列
*/

/**
题意：有n(<=200000)个数排成一列，求长度不超过k(1<=k<=n)的连续的子串的和的最大值.
设dp[i]表示以a[i]为结尾的连续子串和的最大值，状态转移方程：
dp[i] = sum[i] - min{sum[j-1]}, max(0,i-k+1)<=j<i. dp[0]=0 最后结果为max{dp[i],1<=i<=n}

分析：
单纯二重循环O(n*k)肯定超时.
考虑求sum[j-1]的最小值 max(0,i-k)<=j<i,是否可以优化?
1.显然优先级队列可以适用,维护堆,时间复杂度优化为nlogk
2.考虑求解的单调性,若i<j且sum[i]>sum[j],则i可以被舍弃.只要维护一个递增的单调队列即可!
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF = 0x7fffffff;
const int N = 200005;
int n,k;
int a[N];
int sum[N];
int que[N];
int result,st,end;

void solve()
{
    int head=1,tail=0;
    result = -INF;
    st = INF;
    for(int i = 1; i <= n+k; i++)
    {
        while(head<=tail&&sum[i-1]<sum[que[tail]])
            tail--;
        while(head<=tail&&que[head]<i-k)
            head++;
        tail++;
        que[tail] = i-1;
        //output start
        if(sum[i]-sum[que[head]]>result)
        {
            result = sum[i]-sum[que[head]];
            st = que[head]+1;
            end = i;
        }
        //output end
    }
    if(end>n)
        end -= n;
}

int main()
{
    int i;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        sum[0] = 0;
        scanf("%d %d",&n,&k);
        for(i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            sum[i] = sum[i-1] + a[i];
        }
        for(i = n+1; i <= n+k; i++)
            sum[i] = sum[i-1] + a[i-n];
        solve();
        printf("%d %d %d\n",result,st,end);
    }
    return 0;
}
