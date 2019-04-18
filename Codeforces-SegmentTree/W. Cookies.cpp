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

const int maxn = 1e6+10;
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
struct T
{
    int l,r,mid;
    ll num,sum;
}tree[maxn<<2];
int x[maxn],t[maxn];
void up(int rt)
{
    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
    tree[rt].num=tree[rt<<1].num+tree[rt<<1|1].num;
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].num=0;
    tree[rt].sum=0;
    if(l==r) return ;
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
}
void update(int rt,int pos,ll cnt)
{
    if(tree[rt].l==tree[rt].r)
    {
        tree[rt].num+=cnt;
        tree[rt].sum+=1LL*pos*cnt;
        return ;
    }
    if(tree[rt].mid>=pos) update(rt<<1,pos,cnt);
    else update(rt<<1|1,pos,cnt);
    up(rt);
}
ll query(int rt,ll t)
{
    if(tree[rt].l==tree[rt].r) return min(t/tree[rt].l,tree[rt].num);
    if(tree[rt<<1].sum>t) return query(rt<<1,t);
    else return tree[rt<<1].num+query(rt<<1|1,t-tree[rt<<1].sum);
}
vector<int> G[maxn];
vector<ll> W[maxn];
ll ans[maxn];
ll dfs(int rt,ll le)
{
    update(1,t[rt],x[rt]);
   // dbg2(rt,le);
    ll res=query(1,le);
    ll max1=0,max2=0;
    for(int i=0;i<G[rt].size();i++)
    {
        int to=G[rt][i];
        if(le<=2LL*W[rt][i]) continue;
        ll tt=dfs(to,le-2LL*W[rt][i]);
        if(tt>max1) max2=max1,max1=tt;
        else if(tt>max2) max2=tt;
    }
    update(1,t[rt],-x[rt]);
    if(rt==1) return max(res,max1);
    else return max(res,max2);
}
vector<ll> tt;
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    build(1,1,1000000);
    int n;
    ll le;
    scanf("%d%lld",&n,&le);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    for(int i=1;i<=n;i++) scanf("%d",&t[i]);
    for(int i=2;i<=n;i++)
    {
        int fa;
        ll w;
        scanf("%d%lld",&fa,&w);
        G[fa].push_back(i);
        W[fa].push_back(w);
    }
    printf("%lld\n",dfs(1,le));
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
