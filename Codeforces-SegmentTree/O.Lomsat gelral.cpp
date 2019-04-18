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

const int maxn = 1e5+5;
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
#define dbg3(x1,x2,x3) cout<<#x1<<" = "<<x1<<" "<<#x2<<" = "<<x2<<" "<<#x3<<" = "<<x3<<end
map<int,int> mp[maxn];
map<int,ll> sum[maxn];
vector<int> G[maxn];
int a[maxn];
ll ans[maxn];
void dfs(int rt,int fa)
{
    mp[rt][a[rt]]++;
    sum[rt][1]+=a[rt];
    for(int i=0;i<G[rt].size();i++)
    {
        int to=G[rt][i];
        if(to==fa) continue;
        dfs(to,rt);
        if(mp[to].size()>mp[rt].size())
        {
            swap(sum[rt],sum[to]);
            swap(mp[to],mp[rt]);
        }
        for(map<int,int>::iterator it = mp[to].begin();it!=mp[to].end();++it)
        {
            int fi=(*it).Fi;
            int se=(*it).Se;
            if(mp[rt].find(fi)!=mp[rt].end())
            {
                sum[rt][mp[rt][fi]]-=fi;
                mp[rt][fi]+=se;
                sum[rt][mp[rt][fi]]+=fi;
            }
            else
            {
                mp[rt][fi]+=se;
                sum[rt][mp[rt][fi]]+=fi;
            }
        }
    }
    ans[rt]=sum[rt].rbegin()->second;
    return ;
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
