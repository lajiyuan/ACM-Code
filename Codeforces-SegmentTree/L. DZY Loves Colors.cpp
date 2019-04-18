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
    int col,add;
    ll sum,inc;
}tree[maxn<<2];
int col[maxn];
void up(int rt)
{
    if(tree[rt<<1].col==tree[rt<<1|1].col) tree[rt].col=tree[rt<<1].col;
    else tree[rt].col=0;

    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
}
int maxx=0;
void down(int rt)
{
    if(tree[rt].add!=0)
    {
        int tmp=tree[rt].add;
        tree[rt<<1].col=tmp;
        tree[rt<<1].add=tmp;

        tree[rt<<1|1].col=tmp;
        tree[rt<<1|1].add=tmp;
        tree[rt].add=0;
    }

    if(tree[rt].inc!=0)
    {
        ll tmp=tree[rt].inc;
        tree[rt<<1].sum+=1LL*tmp*(tree[rt<<1].r-tree[rt<<1].l+1);
        tree[rt<<1].inc+=tmp;
        tree[rt<<1|1].sum+=1LL*tmp*(tree[rt<<1|1].r-tree[rt<<1|1].l+1);
        tree[rt<<1|1].inc+=tmp;

        tree[rt].inc=0;
    }

}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].add=0;
    tree[rt].inc=0;
    if(l==r)
    {
        tree[rt].col=col[l];
        tree[rt].sum=0;
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    up(rt);
    return ;
}
void update(int rt,int l,int r,int co)
{
    if(tree[rt].l>r||tree[rt].r<l) return ;
    if(tree[rt].l>=l&&tree[rt].r<=r&&tree[rt].col!=0)
    {
        tree[rt].sum=tree[rt].sum+1LL*abs(co-tree[rt].col)*(tree[rt].r-tree[rt].l+1);
        tree[rt].inc+=abs(co-tree[rt].col);
        tree[rt].col=co;
        tree[rt].add=co;
        return ;
    }
    down(rt);
    if(tree[rt].mid>=l) update(rt<<1,l,r,co);
    if(tree[rt].mid<r) update(rt<<1|1,l,r,co);
    up(rt);
}
ll query(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return 0;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].sum;
    down(rt);
    ll ans=0;
    if(tree[rt].mid>=l) ans=ans+query(rt<<1,l,r);
    if(tree[rt].mid<r) ans=ans+query(rt<<1|1,l,r);
    return ans;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) col[i]=i;
    build(1,1,n);
    int cnt=0;
    while(m--)
    {
        int op,x,y,z;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d%d%d",&x,&y,&z);
            update(1,x,y,z);
        }
        else
        {
            scanf("%d%d",&x,&y);
            printf("%lld\n",query(1,x,y));
        }
    }
    return 0;
}
