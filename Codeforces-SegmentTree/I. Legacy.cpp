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
const int maxm = 4e6+5;
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
    int val,id;
}tree[2][maxn<<2];
int mp[2][maxn];// id in tree
struct P
{
    int to;
    ll cost;
    bool operator < (const P & a) const
    {
        return cost>a.cost;
    }
};
struct node
{
    int to,val;
    int nxt;
}edge[maxm];
int head[maxn<<3],tot;//head和tot记得重置，head重置为-1
int id;//点数，边数，不要再main里面重新定义
bool vis[maxn<<3];//每次在dij里面初始化为0
ll dis[maxn<<3];//根据题意初始化为inf可能int可能longlong
void addedge(int x,int y,int val)
{
    edge[tot].to=y;
    edge[tot].val=val;
    edge[tot].nxt=head[x];
    head[x]=tot++;
}
void Dijkstra(int s)
{
    memset(vis,0,sizeof(vis));
    fill(dis,dis+id+2,LL_INF);
    dis[s]=0;
    priority_queue<P>q;
    q.push(P{s,0});
    while(!q.empty())
    {
        P p1=q.top();q.pop();
        int u=p1.to;
        if(vis[u])continue;
        vis[u]=1;
        for(int i=head[u];i+1;i=edge[i].nxt)
        {
            int v=edge[i].to;
            if(vis[v])continue;
            if(dis[v]>dis[u]+edge[i].val)
            {
                dis[v]=dis[u]+edge[i].val;
                q.push(P{v,dis[v]});
            }
        }
    }
}
void link(int p,int rt)
{
    if(p==0)
    {
        addedge(tree[p][rt].id,tree[p][rt<<1].id,0);
        addedge(tree[p][rt].id,tree[p][rt<<1|1].id,0);
    }
    else
    {
        addedge(tree[p][rt<<1].id,tree[p][rt].id,0);
        addedge(tree[p][rt<<1|1].id,tree[p][rt].id,0);
    }
}
void build(int p,int rt,int l,int r)
{
    tree[p][rt].l=l;
    tree[p][rt].r=r;
    tree[p][rt].id=++id;
    if(l==r)
    {
        mp[p][l]=id;
        return ;
    }
    int mid=tree[p][rt].mid=l+r>>1;
    build(p,rt<<1,l,mid);
    build(p,rt<<1|1,mid+1,r);
    link(p,rt);
}
void query(int p,int rt,int l,int r,int u,int val)
{
    if(tree[p][rt].l>r||tree[p][rt].r<l) return ;
    if(tree[p][rt].l>=l&&tree[p][rt].r<=r)
    {
        if(p==0) addedge(u,tree[p][rt].id,val);
        else addedge(tree[p][rt].id,u,val);
        return ;
    }
    if(tree[p][rt].mid>=l) query(p,rt<<1,l,r,u,val);
    if(tree[p][rt].mid<r) query(p,rt<<1|1,l,r,u,val);
    return ;
}

int main()
{
    int n,m,s;
    scanf("%d%d%d",&n,&m,&s);
    memset(head,-1,sizeof(head));
    build(0,1,1,n);
    build(1,1,1,n);
    for(int i=1;i<=n;i++)
    {
        addedge(mp[0][i],mp[1][i],0);
        addedge(mp[1][i],mp[0][i],0);
    }
    while(m--)
    {
        int op,l,r,u,v,w;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d%d%d",&v,&u,&w);
            addedge(mp[0][v],mp[1][u],w);
            addedge(mp[1][v],mp[0][u],w);
        }
        else if(op==2)
        {
            scanf("%d%d%d%d",&v,&l,&r,&w);
            query(0,1,l,r,mp[1][v],w);
        }
        else
        {
            scanf("%d%d%d%d",&v,&l,&r,&w);
            query(1,1,l,r,mp[0][v],w);
        }
    }
    Dijkstra(mp[0][s]);
    for(int i=1;i<=n;i++)
    {
        if(dis[mp[0][i]]==LL_INF) printf("-1 ");
        else printf("%lld ",dis[mp[0][i]]);
    }
    return 0;
}
