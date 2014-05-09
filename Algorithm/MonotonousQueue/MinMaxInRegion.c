/**
移动区间(长度固定)最值问题

单调队列：
加入找最小数，考虑顺序a,b(b在a的后面)，若b<a,当b入队列后，a不可能称为最小值(a比b先出)，删去。
每个元素出队列和入队列一次，时间复杂度为O(n)
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1100000;
int n,k;
int a[N];
int DanDiao_Que[N];     //单调递减队列(最大),单调递增队列(最小)
int head,tail;

//递增
void Min()
{
    int i;
    int head = 1;
    int tail = 0;
    for(i = 0; i < k-1; i++)
    {
        while(head<=tail && a[DanDiao_Que[tail]]>=a[i]) tail--;
        tail++;
        DanDiao_Que[tail] = i;
    }
    for(i = k-1; i < n; i++)
    {
        while(head<=tail && a[DanDiao_Que[tail]]>=a[i]) tail--;
        tail++;
        DanDiao_Que[tail] = i;
        while(DanDiao_Que[head]< i-k+1) head++;
        printf("%d",a[DanDiao_Que[head]]);
        printf("%c",i==n-1?'\n':' ');
    }
}

//递减
void Max()
{
    int i;
    int head = 1;
    int tail = 0;
    for(i = 0; i < k-1; i++)
    {
        while(head<=tail && a[DanDiao_Que[tail]]<=a[i]) tail--;
        tail++;
        DanDiao_Que[tail] = i;
    }
    for(i = k-1; i < n; i++)
    {
        while(head<=tail && a[DanDiao_Que[tail]]<=a[i]) tail--;
        tail++;
        DanDiao_Que[tail] = i;
        while(DanDiao_Que[head]< i-k+1) head++;
        printf("%d",a[DanDiao_Que[head]]);
        printf("%c",i==n-1?'\n':' ');
    }
}

int main()
{
    scanf("%d %d",&n,&k);
    for(int i = 0 ;i < n; i++)
        scanf("%d",&a[i]);
    Min();
    Max();
    return 0;
}
