const int maxn = 5;
int C[maxn][maxn];
char pre[maxn],post[maxn];
int n,m;

void prepare()
{
    memset(C,0,sizeof(C));
    for(int i=0;i<maxn;i++)
    {
        C[i][0] = 1;
    }
    for(int i=1;i<maxn;i++)
    {
        for(int j=1;j<=i;j++)
        {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
    return;
}

int dfs(int rs,int rt,int os,int ot)
{
    if(rs == rt) return 1;
    int son = 0,res = 1;
    int l = rs + 1,r = os;
    while(l <= rt)
    {
        while(r < ot)
        {
            if(pre[l] == post[r])
            {
                son++;
                break;
            }
            r++;
        }
        res *= dfs(l , l + r - os , os , r);
        l += r - os + 1;
        rs = l - 1;
        os = ++r;
    }
    return res * C[m][son];
}
