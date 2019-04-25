#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 1e5+5;
const int Mod=1000000007;
double dp[maxn];
vector<int> G[maxn];
int main()
{
    for(int i=1;i<=100000;i++)
    {
        for(int j=i;j<=100000;j+=i)
        {
            G[j].push_back(i);
        }
    }
    for(int i=2;i<=100000;i++)
    {
        int cnt=G[i].size();
        for(int j=0;j<G[i].size()-1;j++)
        {
            dp[i]=dp[i]+1.0*(dp[G[i][j]]+1.0)/cnt;
        }
        dp[i]=dp[i]+1.0/cnt;
        dp[i]=1.0*dp[i]*cnt/(cnt-1);
    }
    int t;
    scanf("%d",&t);
    int cc=0;
    while(t--)
    {
        int n;
        scanf("%d",&n);
        printf("Case %d: %.10f\n",++cc,dp[n]);
    }

    return 0;
}
