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

const int maxn = 1e6+5;
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
struct data
{
    int op;
    int x,y;
}Q[maxn];
int n,m,q;
struct T
{
    int l,r,mid;
    int sum,add;
}tree[maxn<<2];
vector<int>G[maxn];
void down(int rt)
{
    if(tree[rt].add)
    {
        tree[rt<<1].sum=(tree[rt<<1].r-tree[rt<<1].l+1)-tree[rt<<1].sum;
        tree[rt<<1|1].sum=(tree[rt<<1|1].r-tree[rt<<1|1].l+1)-tree[rt<<1|1].sum;
        tree[rt<<1].add=1-tree[rt<<1].add;
        tree[rt<<1|1].add=1-tree[rt<<1|1].add;
        tree[rt].add=0;
    }
}
void up(int rt)
{
    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].sum=0;
    tree[rt].add=0;
    if(l==r) return;
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
}
bool update(int rt,int pos,int val)
{
    if(tree[rt].l==tree[rt].r)
    {
        int tt=tree[rt].sum;
        tree[rt].sum=val;
        return (tt!=val);
    }
    down(rt);
    bool ans;
    if(tree[rt].mid>=pos) ans=update(rt<<1,pos,val);
    else ans=update(rt<<1|1,pos,val);
    up(rt);
    return ans;
}
void update_(int rt,int l,int r)
{
   // dbg3(rt,tree[rt].l,tree[rt].r);
   // dbg2(l,r);
    if(tree[rt].l>r||tree[rt].r<l) return ;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        tree[rt].add=1-tree[rt].add;
        tree[rt].sum=tree[rt].r-tree[rt].l+1-tree[rt].sum;
        return ;
    }
    down(rt);
    if(tree[rt].mid>=l) update_(rt<<1,l,r);
    if(tree[rt].mid<r) update_(rt<<1|1,l,r);
    up(rt);
}
int ans[maxn];
void dfs(int rt)
{
   // dbg(rt);
    int flag=0;
    if(rt!=0)
    {
        if(Q[rt].op==1)
        {
            if(update(1,(Q[rt].x-1)*m+Q[rt].y,1)) flag=1;
        }
        else if(Q[rt].op==2)
        {
            if(update(1,(Q[rt].x-1)*m+Q[rt].y,0)) flag=1;
        }
        else if(Q[rt].op==3) update_(1,(Q[rt].x-1)*m+1,Q[rt].x*m);
    }
    ans[rt]=tree[1].sum;
    for(int i=0;i<G[rt].size();i++)
    {
        dfs(G[rt][i]);
    }
    if(rt!=0)
    {
        if(Q[rt].op==1&&flag==1) update(1,(Q[rt].x-1)*m+Q[rt].y,0);
        else if(Q[rt].op==2&&flag==1) update(1,(Q[rt].x-1)*m+Q[rt].y,1);
        else if(Q[rt].op==3) update_(1,(Q[rt].x-1)*m+1,Q[rt].x*m);
    }
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&Q[i].op);
        if(Q[i].op==1||Q[i].op==2)
        {
            G[i-1].push_back(i);
            scanf("%d%d",&Q[i].x,&Q[i].y);
        }
        else if(Q[i].op==3)
        {
            G[i-1].push_back(i);
            scanf("%d",&Q[i].x);
        }
        else
        {
            scanf("%d",&Q[i].x);
            G[Q[i].x].push_back(i);
        }
    }
    build(1,1,n*m);
    dfs(0);
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
