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
    pii add;
    int flag;
}tree[maxn<<2];
int a[maxn],b[maxn];
int n,m;
void push_down(int rt)
{
    if(tree[rt].flag==1&&tree[rt].add!=pii(n+1,1))
    {
        pii tmp=tree[rt].add;
        tree[rt<<1].add=tmp;
        tree[rt<<1|1].add=tmp;
        tree[rt<<1].flag=1;
        tree[rt<<1|1].flag=1;
        tree[rt].flag=0;
        return ;
    }
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].flag=0;
    tree[rt].add=pii(n+1,1);
    if(l==r) return ;
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
}
void update(int rt,int l,int r,pii val)
{
    if(tree[rt].l>r||tree[rt].r<l) return ;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        tree[rt].add=val;
        tree[rt].flag=1;
        return ;
    }
    push_down(rt);
   // dbg2(rt,tree[rt].mid);
    if(tree[rt].mid>=l) update(rt<<1,l,r,val);
    if(tree[rt].mid<r) update(rt<<1|1,l,r,val);
}
int query(int rt,int pos)
{
    if(tree[rt].l==tree[rt].r)
    {
        pii tmp=tree[rt].add;
        return a[tmp.Fi+pos-tmp.Se];
    }
    push_down(rt);
    if(tree[rt].mid>=pos) return query(rt<<1,pos);
    else return query(rt<<1|1,pos);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) a[i+n]=b[i];
    build(1,1,n);
    while(m--)
    {
        int op;
        scanf("%d",&op);
        if(op==1)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            update(1,y,y+z-1,pii(x,y));
        }
        else
        {
            int x;
            scanf("%d",&x);
            printf("%d\n",query(1,x));
        }
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
