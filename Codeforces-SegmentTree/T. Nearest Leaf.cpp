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

const int maxn = 5e5+5;
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
ll dis[maxn];
int in[maxn],ou[maxn],t,vis[maxn];
vector<int>G[maxn];
vector<int>W[maxn];
void dfs(int rt,ll cnt)
{
    in[rt]=t+1;
    if(G[rt].size()==0)
    {
        ++t;
        vis[rt]=t;
        dis[t]=cnt;
    }
    for(int i=0;i<G[rt].size();i++)
    {
        int to=G[rt][i];
        dfs(to,cnt+W[rt][i]);
    }
    ou[rt]=t;
}
struct T
{
    int l,r,mid;
    ll add,val;
}tree[maxn<<2];
void up(int rt)
{
    tree[rt].val=min(tree[rt<<1].val,tree[rt<<1|1].val);
}
void down(int rt)
{
    if(tree[rt].add)
    {
        ll tmp=tree[rt].add;
        tree[rt<<1].add+=tmp;
        tree[rt<<1|1].add+=tmp;
        tree[rt<<1].val+=tmp;
        tree[rt<<1|1].val+=tmp;
        tree[rt].add=0;
    }
}
void build(int rt, int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].add=0;
    if(l==r)
    {
        //dbg2(rt,l);
        tree[rt].val=dis[l];
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    up(rt);
}
void update(int rt,int l,int r,ll val)
{
    if(tree[rt].l>r||tree[rt].r<l) return ;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        tree[rt].val+=val;
        tree[rt].add+=val;
        return ;
    }
    down(rt);
    if(tree[rt].mid>=l) update(rt<<1,l,r,val);
    if(tree[rt].mid<r) update(rt<<1|1,l,r,val);
    up(rt);
}
ll query(int rt,int l,int r)
{
   // dbg2(l,r);
    if(tree[rt].l>r||tree[rt].r<l) return LL_INF;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].val;
    down(rt);
    ll res=LL_INF;
    //dbg(tree[rt].mid);
    if(tree[rt].mid>=l) res=min(res,query(rt<<1,l,r));
    if(tree[rt].mid<r) res=min(res,query(rt<<1|1,l,r));
    return res;
}
struct Q
{
    int id;
    int l,r;
    Q(){}
    Q(int _id,int _l,int _r)
    {
        id=_id;
        l=_l;
        r=_r;
    }
};
vector<Q> que[maxn];
int n,q;
ll ans[maxn];
void dfs2(int rt,ll dis)
{
//    dbg2(rt,dis);
//    dbg(tree[4].val);
    update(1,in[rt],ou[rt],-dis);
    //dbg(tree[4].val);
    if(in[rt]>1) update(1,1,in[rt]-1,dis);
    if(ou[rt]<t) update(1,ou[rt]+1,t,dis);
   // dbg(tree[4].val);
   // dbg(tree[1].val);
    for(int i=0;i<que[rt].size();i++) ans[que[rt][i].id]=query(1,que[rt][i].l,que[rt][i].r);
    for(int i=0;i<G[rt].size();i++) dfs2(G[rt][i],W[rt][i]);
    update(1,in[rt],ou[rt],dis);
    if(in[rt]>1) update(1,1,in[rt]-1,-dis);
    if(ou[rt]<t) update(1,ou[rt]+1,t,-dis);
}
int pre[maxn],nex[maxn];
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int x,w;
    scanf("%d%d",&n,&q);
    for(int i=2;i<=n;i++)
    {
        scanf("%d%d",&x,&w);
        G[x].pb(i);
        W[x].pb(w);
    }
    dfs(1,0);
   // for(int i=1;i<=t;i++) dbg2(i,dis[i]);
   // for(int i=1;i<=n;i++) dbg2(in[i],ou[i]);
    build(1,1,t);
    int ppre=-1;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]!=0) ppre=vis[i];
        pre[i]=ppre;
    }
    int nexx=-1;
    for(int i=n;i>=1;i--)
    {
        if(vis[i]!=0) nexx=vis[i];
        nex[i]=nexx;
    }
   // for(int i=1;i<=n;i++) dbg3(i,pre[i],nex[i]);
    for(int i=1;i<=q;i++)
    {
        int rt,l,r;
        scanf("%d%d%d",&rt,&l,&r);
        que[rt].push_back(Q(i,nex[l],pre[r]));
    }

    dfs2(1,0);
    for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
    //cout << "time: " << (lo   ng long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
