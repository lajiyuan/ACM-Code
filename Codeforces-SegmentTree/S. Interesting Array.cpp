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
    int sum,add;
}tree[maxn<<2];
void push_up(int rt)
{
    tree[rt].sum=tree[rt<<1].sum&tree[rt<<1|1].sum;
}
void push_down(int rt)
{
    if(tree[rt].add!=0)
    {
        int tmp=tree[rt].add;
        tree[rt<<1].add=tree[rt<<1].add|tmp;
        tree[rt<<1].sum=tree[rt<<1].sum|tmp;
        tree[rt<<1|1].add=tree[rt<<1|1].add|tmp;
        tree[rt<<1|1].sum=tree[rt<<1|1].sum|tmp;
        tree[rt].add=0;
    }
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].sum=0;
    tree[rt].add=0;
    if(l==r) return ;
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    return ;
}
void update(int rt,int l,int r,int val)
{
    if(tree[rt].l>r||tree[rt].r<l) return ;
    if(tree[rt].sum==tree[rt].r-tree[rt].l+1) return ;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        tree[rt].sum=tree[rt].sum|val;
        tree[rt].add=tree[rt].add|val;
        return ;
    }
    push_down(rt);
    if(tree[rt].mid>=l) update(rt<<1,l,r,val);
    if(tree[rt].mid<r) update(rt<<1|1,l,r,val);
    push_up(rt);
    return ;
}
int query(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return 0;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].sum;
    push_down(rt);
    int ans=(1<<30)-1;
    if(tree[rt].mid>=l) ans=ans&query(rt<<1,l,r);
    if(tree[rt].mid<r) ans=ans&query(rt<<1|1,l,r);
    push_up(rt);
    return ans;
}
int ans[maxn];
inline bool read(int &num)
{
    char in;bool IsN=false;
    in=getchar();
    if(in==EOF) return false;
    while(in!='-'&&(in<'0'||in>'9')) in=getchar();
    if(in=='-')
    {
        IsN=true;
        num=0;
    }
    else num=in-'0';
    while(in=getchar(),in>='0'&&in<='9')
    {
            num*=10,num+=in-'0';
    }
    if(IsN) num=-num;
    return true;
}
map<pii,int> mp;
int main()
{
    int n,m,l,r,q;
    read(n);
    read(m);
    build(1,1,n);
    int flag=0;
    for(int i=1;i<=m;i++)
    {
        read(l);
        read(r);
        read(q);
        if(mp.count(pii(l,r)))
        {
            if(mp[pii(l,r)]!=q) flag=1;
        }
        mp[pii(l,r)]=q;
        if(flag==1) continue;
        int res=query(1,l,r);
        if((q&res)==res)
        {
            int tmp=q-res;
            update(1,l,r,tmp);
        }
        else flag=1;
    }
    if(flag==1) return 0*puts("NO");
    for(int i=1;i<=n;i++) ans[i]=query(1,i,i);
    puts("YES");
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
