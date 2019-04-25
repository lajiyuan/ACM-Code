#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
using namespace std;
const double eps = 1e-10;
const int maxn = 1e5+5;
int sgn(double x)
{
    if(fabs(x)<eps) return 0;
    if(x<0) return -1;
    return 1;
}
struct data
{
    int m;
    double p;
}x[maxn];
double dp[105][10005];
int main()
{
    int t;
    scanf("%d",&t);
    int cc=0;
    while(t--)
    {
        int n;
        double p;
        scanf("%lf%d",&p,&n);
        for(int i=1;i<=n;i++) scanf("%d%lf",&x[i].m,&x[i].p);
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<=10000;j++)
            {
                dp[i][j]=dp[i-1][j];
                if(j>=x[i].m) dp[i][j]=max(dp[i][j],dp[i-1][j-x[i].m]*(1-x[i].p));
                if(sgn(dp[i][j]-1.0+p)>=0) ans=max(ans,j);
            }
        }
        printf("Case %d: %d\n",++cc,ans);
    }
    return 0;
}
