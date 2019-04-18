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
struct T
{
    int l,r,mid;
    int val;
}tree[maxn<<2];
void push_up(int rt)
{
    tree[rt].val=tree[rt<<1].val+tree[rt<<1|1].val;
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].val=0;
    if(l==r) return ;
    int mid = tree[rt].mid = l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    push_up(rt);
}
void update(int rt,int pos)
{
    if(tree[rt].l==tree[rt].r)
    {
        tree[rt].val++;
        return ;
    }
    if(pos<=tree[rt].mid) update(rt<<1,pos);
    else update(rt<<1|1,pos);
    push_up(rt);
}
int query(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return 0;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].val;
    int ans=0;
    if(tree[rt].mid>=l) ans+=query(rt<<1,l,r);
    if(tree[rt].mid<r) ans+=query(rt<<1|1,l,r);
    return ans;
}
int pre[maxn],suf[maxn];
int a[maxn],d;//原数组
int b[maxn];//每个位置离散后的值
int c[maxn];//表示离散后为i的原来的值为c[i]
int Hash[maxn];//hash去重数组
void GetHash(int a[],int n)
{
    for(int i=1;i<=n;i++) Hash[i]=a[i];
    sort(Hash+1,Hash+1+n);
    d=unique(Hash+1,Hash+1+n)-Hash-1;
    for(int i=1;i<=n;i++)
    {
        b[i]=lower_bound(Hash+1,Hash+1+d,a[i])-Hash;
        c[b[i]]=a[i];
    }
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    GetHash(a,n);
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        pre[i]=query(1,b[i]+1,d);
        update(1,b[i]);
    }
    build(1,1,n);
    for(int i=n;i>=1;i--)
    {
        suf[i]=query(1,1,b[i]-1);
        update(1,b[i]);
    }
    ll ans=0;
    for(int i=1;i<=n;i++) ans=ans+1LL*pre[i]*suf[i];
    printf("%lld\n",ans);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
