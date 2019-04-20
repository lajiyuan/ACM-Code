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
int a[maxn];
ll dp[maxn];
struct T
{
    int l,r,mid;
    ll val;
}tree[maxn<<2];
void up(int rt)
{
    if(a[tree[rt<<1].val]>a[tree[rt<<1|1].val]) tree[rt].val=tree[rt<<1].val;
    else tree[rt].val=tree[rt<<1|1].val;
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    if(l==r)
    {
        tree[rt].val=l;
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    up(rt);
}
int query(int rt,int l,int r)
{
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].val;
    int ans=0;
    if(tree[rt].mid>=l) ans=query(rt<<1,l,r);
    if(tree[rt].mid<r)
    {
        if(ans==0) ans=query(rt<<1|1,l,r);
        else
        {
            int tt=query(rt<<1|1,l,r);
            if(a[tt]>a[ans])  ans=tt;
        }
    }
    return ans;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++) scanf("%d",&a[i]);
    a[n]=n;
    build(1,1,n);
    dp[n]=0;
    for(int i=n-1;i>=1;i--)
    {
        int pos=query(1,i+1,a[i]);
        dp[i]=dp[pos]+n-i-(a[i]-pos);//注意a[pos]>a[i],不然无法到达终点。
    }
    ll ans=0;
    for(int i=1;i<=n;i++) ans=ans+dp[i];
    printf("%lld\n",ans);
    return 0;
}
