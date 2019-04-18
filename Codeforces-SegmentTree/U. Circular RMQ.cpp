#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<queue>
#include<map>
#include<bitset>
#include<sstream>
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
    ll val,add;
}tree[maxn<<2];
int a[maxn];
void push_up(int rt)
{
    tree[rt].val=min(tree[rt<<1].val,tree[rt<<1|1].val);
}
void push_down(int rt)
{
    if(tree[rt].add)
    {
        int tmp=tree[rt].add;
        tree[rt<<1].val+=tmp;
        tree[rt<<1|1].val+=tmp;
        tree[rt<<1].add+=tmp;
        tree[rt<<1|1].add+=tmp;
        tree[rt].add=0;
    }
    return ;
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
    push_up(rt);
}
void update(int rt,int l,int r,int val)
{
    if(tree[rt].l>r||tree[rt].r<l) return ;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        tree[rt].add+=val;
        tree[rt].val+=val;
        return ;
    }
    push_down(rt);
    if(tree[rt].mid>=l) update(rt<<1,l,r,val);
    if(tree[rt].mid<r) update(rt<<1|1,l,r,val);
    push_up(rt);
    return ;
}
ll query(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return LL_INF;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].val;
    push_down(rt);
    ll ans=LL_INF;
    if(tree[rt].mid>=l) ans=min(ans,query(rt<<1,l,r));
    if(tree[rt].mid<r) ans=min(ans,query(rt<<1|1,l,r));
    push_up(rt);
    return ans;
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    int q;
    scanf("%d",&q);
    getchar();
    while(q--)
    {
        string tmp;
        getline(cin,tmp);
        stringstream ss(tmp);
        int x[4];
        int cnt=0;
        while(ss>>x[++cnt]) ;
        cnt--;
        if(cnt==2)
        {
            x[1]++;
            x[2]++;
            if(x[2]<x[1])
            {
                ll ans1=query(1,1,x[2]);
                ll ans2=query(1,x[1],n);
                printf("%lld\n",min(ans1,ans2));
            }
            else
            {
                printf("%lld\n",query(1,x[1],x[2]));
            }
        }
        else
        {
            x[1]++;
            x[2]++;
            if(x[2]<x[1])
            {
                update(1,1,x[2],x[3]);
                update(1,x[1],n,x[3]);
            }
            else
            {
                update(1,x[1],x[2],x[3]);
            }

        }

    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
