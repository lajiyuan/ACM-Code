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

const int maxn = 3e5+5;
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
    int val;
    ll sum;
}tree[maxn<<2];
int a[maxn];
int sml[1000005];
void push_up(int rt)
{
    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
    tree[rt].val=max(tree[rt<<1].val,tree[rt<<1|1].val);
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    if(l==r)
    {
        tree[rt].sum=a[l];
        tree[rt].val=a[l];
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    push_up(rt);
}
int query_max(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return 0;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].val;
    int ans=0;
    if(tree[rt].mid>=l) ans=max(ans,query_max(rt<<1,l,r));
    if(tree[rt].mid<r) ans=max(ans,query_max(rt<<1|1,l,r));
    return ans;
}
void update(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return ;
    if(tree[rt].l==tree[rt].r)
    {
        tree[rt].val=sml[tree[rt].val];
        tree[rt].sum=tree[rt].val;
        return ;
    }
    if(tree[rt].mid>=l&&query_max(rt<<1,l,r)>2) update(rt<<1,l,r);
    if(tree[rt].mid<r&&query_max(rt<<1|1,l,r)>2) update(rt<<1|1,l,r);
    push_up(rt);
}
ll query(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return 0;
    if(tree[rt].l>=l&&tree[rt].r<=r)  return tree[rt].sum;
    ll ans=0;
    if(tree[rt].mid>=l) ans=ans+query(rt<<1,l,r);
    if(tree[rt].mid<r) ans=ans+query(rt<<1|1,l,r);
    return ans;
}
void init()
{
    for(int i=1;i<=1000000;i++)
    {
        for(int j=i;j<=1000000;j+=i)
        {
            sml[j]++;
        }
    }
}
int main()
{
    init();
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==2) printf("%lld\n",query(1,x,y));
        else update(1,x,y);
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
