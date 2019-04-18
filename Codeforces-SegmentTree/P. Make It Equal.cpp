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

const int maxn = 4e5+5;
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
    ll add,val;
}tree[maxn<<2];
ll a[maxn];
ll sum[maxn];
ll b[maxn];
void up(int rt)
{
    tree[rt].val=min(tree[rt<<1].val,tree[rt<<1|1].val);
    return;
}
void down(int rt)
{
    if(tree[rt].add!=0)
    {
        ll tmp=tree[rt].add;
        tree[rt<<1].val+=tmp;
        tree[rt<<1|1].val+=tmp;
        tree[rt<<1].add+=tmp;
        tree[rt<<1|1].add+=tmp;
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
        tree[rt].val=b[l];
      //  dbg(tree[rt].val);
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    up(rt);
}
pll query(int rt,int l,int r,ll val)
{
    if(tree[rt].val>val) return pll(-1,-1);
    if(tree[rt].l==tree[rt].r) return pll(tree[rt].l,tree[rt].val);
    down(rt);
    if(tree[rt<<1|1].val<=val) return query(rt<<1|1,l,r,val);
    else return query(rt<<1,l,r,val);
}
int main()
{
    //ios::sync_with_stdio(false);
  //  freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    if(a[1]==a[n])//不需要切刀直接特判
    {
        puts("0");
        return 0;
    }
    int pos=1;
    for(int i=1;i<=n;i++)
    {
        while(pos<=200000&&pos<=a[i])
        {
            sum[pos]=(n-i+1);
            pos++;
        }
    }
    for(int i=1;i<=200000;i++) b[i]=sum[200000-i+1];
    int pp;

    for(int i=1;i<=200000;i++)
    {
        if(b[i]==n)
        {
            pp=i;
            break;
        }
    }
    for(int i=1;i<=200000;i++) b[i]=b[i-1]+b[i];
    build(1,1,200000);
    pll tt=pii(0,0);
    int ans=0;
    ll cc=0;
    while(true)
    {
        tt=query(1,1,200000,k);
        ans++;
        tree[1].val-=tt.Se;
        tree[1].add-=tt.Se;
        if(tt.Fi==200000) break;//坑点1，有可能随着前一部分一起消失
        cc+=tt.Se;
        ll tm=b[tt.Fi+1]-cc;
        if(tm==n) break;//注意点
    }
    printf("%d\n",ans);
  //  cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
