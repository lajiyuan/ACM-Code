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
#define dbg3(x1,x2,x3) cout<<#x1<<" = "<<x1<<" "<<#x2<<" = "<<x2<<" "<<#x3<<" = "<<x3<<endl
struct T
{
    int l,r,mid;
    int val;
}tree[maxn<<2];
void push_up(int rt)
{
    tree[rt].val=min(tree[rt<<1].val,tree[rt<<1|1].val);
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;

    if(l==r)
    {
        tree[rt].val=INF;
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    push_up(rt);
}
void update(int rt,int pos,int val)
{
    if(tree[rt].l==tree[rt].r)
    {
        tree[rt].val=val;
        return;
    }
    if(tree[rt].mid>=pos) update(rt<<1,pos,val);
    else update(rt<<1|1,pos,val);
    push_up(rt);
}
int querymin(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return INF;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].val;
    int ans=INF;
    if(tree[rt].mid>=l)  ans=min(ans,querymin(rt<<1,l,r));
    if(tree[rt].mid<r) ans=min(ans,querymin(rt<<1|1,l,r));
    return ans;
}
int query(int rt,int l,int r,int val)
{
    if(tree[rt].l>r||tree[rt].r<l) return INF;
    if(tree[rt].l==tree[rt].r) return tree[rt].l;
    if(tree[rt].mid<r&&querymin(rt,tree[rt].mid+1,r)<val) return query(rt<<1|1,l,r,val);
    else if(tree[rt].mid>=l&&querymin(rt,l,tree[rt].mid)<val) return query(rt<<1,l,r,val);
    else return INF;
}
int a[maxn];
int res[maxn];
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=n;i>=1;i--)
    {
        int ans=query(1,i+1,n,a[i]);
        if(ans==INF) res[i]=-1;
        else res[i]=(ans-i-1);
        update(1,i,a[i]);
      //  dbg2(i,tree[9].val);
    }
    for(int i=1;i<=n;i++) printf("%d%c",res[i],i==n?'\n':' ');
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
