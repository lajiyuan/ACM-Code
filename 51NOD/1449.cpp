#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<queue>
#include<map>
#include<bitset>
#include<stack>
#include<set>
#include<vector>
#include <time.h>
#include<string.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef pair <ll, int> pli;
typedef pair <db, db> pdd;

const int maxn = 1e7+5;
const int Mod=1000000007;
const int INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
const double e=exp(1);
const db PI = acos(-1);
const db ERR = 1e-10;

#define Se second
#define Fi first
#define pb push_back
#define ok cout<<"OK"<<endl
#define dbg(x) cout<<#x<<" = "<< (x)<< endl
#define dbg2(x1,x2) cout<<#x1<<" = "<<x1<<" "<<#x2<<" = "<<x2<<endl
#define dbg3(x1,x2,x3) cout<<#x1<<" = "<<x1<<" "<<#x2<<" = "<<x2<<" "<<#x3<<" = "<<x3<<endl
vector<int> tmp;
int a[maxn];
ll w,m;
int ans1[maxn],cnt1,cnt2,flag;
void dfs1(int pos,int lim,ll sum)
{
    if(pos==lim)
    {
        ans1[++cnt1]=sum;
        return ;
    }
    if(sum+a[pos]<INF) dfs1(pos+1,lim,sum+a[pos]);
    dfs1(pos+1,lim,sum);
    if(sum-a[pos]>-INF) dfs1(pos+1,lim,sum-a[pos]);
}
void dfs2(int pos,int lim,ll sum)
{
    if(flag==1) return ;
    if(pos==lim)
    {
        int pos=lower_bound(ans1+1,ans1+1+cnt1,m-sum)-ans1;
        if(ans1[pos]==m-sum)
        {
            flag=1;
            return ;
        }
        return ;
    }
    if(sum+a[pos]<INF) dfs2(pos+1,lim,sum+a[pos]);
    dfs2(pos+1,lim,sum);
    if(sum-a[pos]>-INF)  dfs2(pos+1,lim,sum-a[pos]);
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);

    scanf("%lld%lld",&w,&m);
    ll tt=1;
    while(tt<=m)
    {
        tmp.push_back(tt);
        tt*=w;
    }
    tmp.push_back(tt);
    int sz=tmp.size();
    int cnta=0,cntb=0;
    for(int i=0;i<sz/2;i++) a[cnta++]=tmp[i];
    dfs1(0,cnta,0);
  //  for(int i=1;i<=cnt1;i++) dbg2(i,ans1[i]);
    sort(ans1+1,ans1+1+cnt1);
    for(int i=sz/2;i<sz;i++) a[cntb++]=tmp[i];
    dfs2(0,cntb,0);
    if(flag==1) puts("YES");
    else puts("NO");
    //cout << "time: /" << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
