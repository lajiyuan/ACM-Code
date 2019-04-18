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
struct T
{
    int l,r,mid;
    ll val,add;
}tree[maxn<<2];
int a[maxn];
void up(int rt)
{
    tree[rt].val=tree[rt<<1].val+tree[rt<<1|1].val;
}
void down(int rt)
{
    if(tree[rt].add)
    {
        ll tmp=tree[rt].add;
        tree[rt<<1].add+=tmp;
        tree[rt<<1].val+=1LL*(tree[rt<<1].r-tree[rt<<1].l+1)*tmp;
        tree[rt<<1|1].add+=tmp;
        tree[rt<<1|1].val+=1LL*(tree[rt<<1|1].r-tree[rt<<1|1].l+1)*tmp;
        tree[rt].add=0;
    }
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].add=0;
    if(l==r)
    {
        tree[rt].val=a[l];
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
        tree[rt].add+=val;
        tree[rt].val+=1LL*(tree[rt].r-tree[rt].l+1)*val;
        return ;
    }
    down(rt);
    if(tree[rt].mid>=l) update(rt<<1,l,r,val);
    if(tree[rt].mid<r) update(rt<<1|1,l,r,val);
    up(rt);
    return ;
}
ll query(int rt,int pos)
{
    if(tree[rt].l==tree[rt].r) return tree[rt].val;
    down(rt);
    if(pos<=tree[rt].mid) return query(rt<<1,pos);
    else return query(rt<<1|1,pos);
}
int l[maxn],r[maxn],val[maxn],cnt[maxn];
int tt[maxn];
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&l[i],&r[i],&val[i]);
    for(int i=1;i<=k;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        tt[u]++;
        tt[v+1]--;
    }
    int tmp=0;
    for(int i=1;i<=m;i++)
    {
        tmp+=tt[i];
        cnt[i]=tmp;
    }

    for(int i=1;i<=m;i++) update(1,l[i],r[i],1LL*cnt[i]*val[i]);

    for(int i=1;i<=n;i++) printf("%lld ",query(1,i));
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
