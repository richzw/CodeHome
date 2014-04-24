/*
给定一个字符串,求至少出现 k 次的最长重复子串,这 k 个子串可以重叠。
*/

#define M 20007
#define MAX 1000010

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
这道题二分求解的是最长长度，每判断mid长度时，需要遍历一下所有的height数组，
看看有没有最长公共前缀长度是mid而且数量大于k的，如果存在，则此mid满足条件，继续二分。
*/
int solve(int n,int k)//binary search
{
    int maxx=n,minn=1;
    while(minn<=maxx){
        int mid=(minn+maxx)/2,count=1,flag=0;
        for(int i=2; i<=n; i++)
            if(height[i]<mid){
				count=1;
			}//Least common prefix less than mid，reset count
            else{
                count++;
                if(count==k)//if find k，this length is correct
                {
                    flag=1;
					break;
                }
            }
        if(flag){
			minn=mid+1;
		}
        else 
			maxx=mid-1;
    }
    return maxx;
}
