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

const int maxn = 2e5+5;
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
int tim;
int t[maxn];
int sum[maxn],sum2[maxn];
int in[maxn],ou[maxn],dfn[maxn];
vector<int> G[maxn];
void dfs(int rt,int fa)
{
    in[rt]=++tim;
    dfn[tim]=rt;
    for(int i=0;i<G[rt].size();i++)
    {
        int to=G[rt][i];
        if(to==fa) continue;
        dfs(to,rt);
    }
    ou[rt]=tim;
}
struct T
{
    int l,r,mid;
    int add,sum;
}tree[maxn<<2];
void push_up(int rt)
{
    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
}
void push_down(int rt)
{
    if(tree[rt].add)
    {
        tree[rt<<1].add^=1;
        tree[rt<<1].sum=(tree[rt<<1].r-tree[rt<<1].l+1)-tree[rt<<1].sum;
        tree[rt<<1|1].add^=1;
        tree[rt<<1|1].sum=(tree[rt<<1|1].r-tree[rt<<1|1].l+1)-tree[rt<<1|1].sum;
        tree[rt].add=0;
    }
}
void build(int rt,int l,int r)
{
    tree[rt].add=0;
    tree[rt].l=l;
    tree[rt].r=r;
    if(l==r)
    {
        tree[rt].sum=t[dfn[l]];//dfs序的问题这里记得dfn
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    push_up(rt);
}
void update(int rt,int l,int r)
{
    if(tree[rt].r<l||tree[rt].l>r) return ;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        tree[rt].sum=(tree[rt].r-tree[rt].l+1)-tree[rt].sum;
        tree[rt].add^=1;
        return ;
    }
    push_down(rt);
    if(tree[rt].mid>=l) update(rt<<1,l,r);
    if(tree[rt].mid<r) update(rt<<1|1,l,r);
    push_up(rt);
}
int query(int rt,int l,int r)
{
    if(tree[rt].r<l||tree[rt].l>r) return 0;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].sum;
    push_down(rt);
    int ans=0;
    if(tree[rt].mid>=l) ans+=query(rt<<1,l,r);
    if(tree[rt].mid<r) ans+=query(rt<<1|1,l,r);
    push_up(rt);
    return ans;
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n,x;
    scanf("%d",&n);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&x);
        G[x].push_back(i);
        G[i].push_back(x);
    }
    for(int i=1;i<=n;i++) scanf("%d",&t[i]);
    dfs(1,-1);
    build(1,1,n);
    int q;
    scanf("%d",&q);
    while(q--)
    {
        char op[4];
        int v;
        scanf("%s%d",op,&v);
        if(op[0]=='p') update(1,in[v],ou[v]);
        else printf("%d\n",query(1,in[v],ou[v]));
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}

