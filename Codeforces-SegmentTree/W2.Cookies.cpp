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
    ll val,add,sum,add2;
}tree[maxn<<2];
int x[maxn],t[maxn];
void up(int rt)
{
    tree[rt].val=min(tree[rt<<1].val,tree[rt<<1|1].val);
    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
}
void down(int rt)
{
    if(tree[rt].add)
    {
        ll tmp=tree[rt].add;
        tree[rt<<1].val+=tmp;
        tree[rt<<1|1].val+=tmp;
        tree[rt<<1].add+=tmp;
        tree[rt<<1|1].add+=tmp;
        tree[rt].add=0;
    }
    if(tree[rt].add2)
    {
        ll tmp=tree[rt].add2;
        tree[rt<<1].sum+=tmp;
        tree[rt<<1|1].sum+=tmp;
        tree[rt<<1].add2+=tmp;
        tree[rt<<1|1].add2+=tmp;
        tree[rt].add2=0;
    }
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].add=0;
    tree[rt].val=0;
    tree[rt].sum=0;
    if(l==r) return ;
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
}
void update(int rt,int l,int r,ll val,ll cnt)
{
    if(tree[rt].l>r||tree[rt].r<l) return ;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        tree[rt].add+=val;
        tree[rt].val+=val;

        tree[rt].sum+=cnt;
        tree[rt].add2+=cnt;
        return ;
    }
    down(rt);
    if(tree[rt].mid>=l) update(rt<<1,l,r,val,cnt);
    if(tree[rt].mid<r) update(rt<<1|1,l,r,val,cnt);
    up(rt);
}
ll query(int rt,ll t)
{
    if(tree[rt].l==tree[rt].r)
    {
        ll tt=tree[rt].l;
        if(tt==1000000) return tree[rt].sum;
        else return tree[rt].sum+((t-tree[rt].val)/(tt+1));
    }
    down(rt);
    if(tree[rt<<1|1].val<=t) return query(rt<<1|1,t);
    else if(tree[rt<<1].val<=t) return query(rt<<1,t);
    else return 0;
}
vector<int> G[maxn];
vector<int> W[maxn];
ll dfs(int rt,ll le)
{
    update(1,t[rt],1000000,1LL*x[rt]*t[rt],x[rt]);
    ll res=query(1,le);
    ll max1=0,max2=0;
    for(int i=0;i<G[rt].size();i++)
    {
        int to=G[rt][i];
        if(le-2LL*W[rt][i]<=0) continue;
        ll tt=dfs(to,le-2LL*W[rt][i]);
        if(tt>max1) max2=max1,max1=tt;
        else if(tt>max2) max2=tt;
    }
    update(1,t[rt],1000000,-1LL*x[rt]*t[rt],-x[rt]);
    if(rt==1) return max(max1,res);
    else return max(max2,res);
}
vector<ll> tt;
int main()
{
    build(1,1,1000000);
    int n;
    ll le;
    scanf("%d%lld",&n,&le);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    for(int i=1;i<=n;i++) scanf("%d",&t[i]);
    for(int i=2;i<=n;i++)
    {
        int fa,w;
        scanf("%d%d",&fa,&w);
        G[fa].push_back(i);
        W[fa].push_back(w);
    }
    printf("%lld\n",dfs(1,le));
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
