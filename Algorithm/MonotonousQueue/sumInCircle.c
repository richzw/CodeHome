//由n(10^6)个数据组成的圆环,数据为1和-1,问从一个点开始顺时针或逆时针,能遍历完所有点,并且保证中间过程中sum>=0
/*
  首先O(n^2)可定不可行。假设从i点开始，这里仅考虑向左，必须保证sum(j,i)>=0,i-n<j<=i.设sum[i]为从开始到i的和，
  即保证sum[i]-sum[j]>=0,i-n<=j<i,即只要保证sum[i]-max{sum[j]}>=0即可。求移动区间(固定长度)最值问题，就可以联想到单调队列了。
  维护操作略。注意顺时针和逆时针计数时判重。
*/

/**
题意:由n(10^6)个数据组成的圆环,数据为1和-1,问从一个点开始顺时针或逆时针,能遍历完所有点,并且保证中间过程中sum>=0。
分析:首先暴力O(n^2)是不可行的。
    假设从i点开始,这里仅考虑向左,必须保证sum(j,i)>=0, i-n <j <= i.
    设sum[i]表示从0到i点的和,即保证sum[i]-sum[j]>=0,即sum[i] - max(sum[j])>=0.
    要求区间[i-n,i-1]最大值,维护单调递减队列即可。
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 2100000;
int n;
char a[N/2];
int num[N];
int sum[N];
int que[N/2];
bool f[N/2],f2[N/2];

void solve(bool t)
{
    int i;
    int head=1,tail=0;
    for(i = 1; i < n; i++)
    {
        while(head<=tail&&sum[que[tail]]<=sum[i]) tail--;
        tail++;
        que[tail] = i;
    }
    for(i = n; i <= 2*n; i++)
    {
        while(head<=tail&&que[head]<i-n) head++;
        while(head<=tail&&sum[que[tail]]<=sum[i]) tail--;
        tail++;
        que[tail] = i;
        if(sum[i]-sum[que[head]]>=0)
        {
            if(t)
                f[i-n] = true;
            else
                f2[i-n] = true;
        }
    }
}

int main()
{
    int i;
    int t;
    int cases = 0;
    scanf("%d",&t);
    while(t--)
    {
        memset(f,0,sizeof(f));
        memset(f2,0,sizeof(f2));
        sum[0] = 0;
        scanf("%s",a+1);
        n = strlen(a+1);
        for(i = 1; i <= n; i++)
        {
            if(a[i]=='C')
                num[i] = 1;
            else
                num[i] = -1;
        }
        for(i = 1; i <= n; i++)
            num[i+n] = num[i];
        for(i = 1; i <= n*2; i++)
            sum[i] = sum[i-1] + num[i];
        //1234512345
        int result = 0;
        solve(true);
        //reverse
        for(i = 1; i <= n; i++)
            sum[i] = sum[i-1] + num[n+1-i];
        for(i = n+1; i <=2*n; i++)
            sum[i] = sum[i-1] + num[2*n+1-i];
        //5432154321
        solve(false);
        result = 0;
        for(i = 0; i < n; i++)
            if(f[i]||f2[n-i])
                result++;
        printf("Case %d: %d\n",++cases,result);
    }
    return 0;
}
