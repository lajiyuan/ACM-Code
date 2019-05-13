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
int a[maxn],l[maxn],r[maxn];
ll sum[maxn];
vector<int> G1[maxn],G2[maxn];
struct data
{
    int l,r;
};
bool cmp(const data &a,const data &b)
{
    if(a.l==b.l) return a.r<b.r;
    return a.l<b.l;
}
struct T
{
    int l,r,mid;
    int sum;
}tree[maxn<<2];
void up(int rt)
{
    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    if(tree[rt].l==tree[rt].r) return ;
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
}
void update(int rt,int pos,int val)
{
    if(tree[rt].l==tree[rt].r)
    {
        tree[rt].sum+=val;
        return ;
    }
    if(pos<=tree[rt].mid) update(rt<<1,pos,val);
    else update(rt<<1|1,pos,val);
    up(rt);
}
int query(int rt,int k)
{
    if(tree[rt].l==tree[rt].r) return tree[rt].l;
    if(k<=tree[rt<<1|1].sum) return query(rt<<1|1,k);
    else return query(rt<<1,k-tree[rt<<1|1].sum);
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n,k,m;
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&l[i],&r[i]);
        G1[l[i]].pb(r[i]);
        G2[r[i]].pb(r[i]);
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<G1[i].size();j++) update(1,G1[i][j],1);
        if(tree[1].sum>=k)
        {
            int pos=query(1,k);
            ans=max(ans,(sum[pos]-sum[i-1]));
        }
        for(int j=0;j<G2[i].size();j++) update(1,G2[i][j],-1);
    }
    printf("%lld\n",ans);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
