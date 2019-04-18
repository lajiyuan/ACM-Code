#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 4e5+5;
const int Mod=1000000007;
ll a[maxn];
int prime[maxn];
int flag[maxn+5];
int tot;
ll pp[maxn];
void init()
{
    for(int i=2;i<=maxn;i++)
    if(!flag[i])
    {
        prime[++tot]=i;
        for(int j=i+i;j<=maxn;j+=i)
            flag[j]=1;
    }
}
vector<int> v;
ll pow_(ll a,ll b)
{
    ll ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%Mod;
        b>>=1;
        a=a*a%Mod;
    }
    return ans;
}
ll inv_(int x)
{
    return pow_(x,Mod-2);
}
struct T
{
    int l,r,mid;
    ll mul,pri,val,tt;
}tree[maxn<<2];
void push_up(int rt)
{
    tree[rt].val=tree[rt<<1].val*tree[rt<<1|1].val%Mod;
    tree[rt].pri=tree[rt<<1].pri|tree[rt<<1|1].pri;
}
void push_down(int rt)
{
    if(tree[rt].mul!=1)
    {
        ll tmp=tree[rt].mul;
        tree[rt<<1].val=tree[rt<<1].val*pow_(tmp,tree[rt<<1].r-tree[rt<<1].l+1)%Mod;
        tree[rt<<1].mul=tree[rt<<1].mul*tmp%Mod;
        tree[rt<<1|1].val=tree[rt<<1|1].val*pow_(tmp,tree[rt<<1|1].r-tree[rt<<1|1].l+1)%Mod;
        tree[rt<<1|1].mul=tree[rt<<1|1].mul*tmp%Mod;
        tree[rt].mul=1;
    }
    if(tree[rt].tt!=0)
    {
        ll tmp=tree[rt].tt;
        tree[rt<<1].pri=tree[rt<<1].pri|tmp;
        tree[rt<<1|1].pri=tree[rt<<1|1].pri|tmp;
        tree[rt<<1].tt|=tmp;
        tree[rt<<1|1].tt|=tmp;
        tree[rt].tt=0;
    }
}
void build(int rt,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    tree[rt].mul=1;
    tree[rt].tt=0;
    if(l==r)
    {
        tree[rt].val=a[l];
        tree[rt].pri=pp[l];
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    push_up(rt);
}
void update(int rt,int l,int r,int x,ll pri)
{
    if(tree[rt].l>r||tree[rt].r<l)  return ;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        tree[rt].val=tree[rt].val*pow_(x,tree[rt].r-tree[rt].l+1)%Mod;
        tree[rt].mul=tree[rt].mul*x%Mod;
        tree[rt].tt|=pri;
        tree[rt].pri|=pri;
        return ;
    }
    push_down(rt);
    if(l<=tree[rt].mid) update(rt<<1,l,r,x,pri);
    if(r>tree[rt].mid) update(rt<<1|1,l,r,x,pri);
    push_up(rt);
    return ;
}
ll query(int rt,int l,int r,ll &pri)
{
    if(tree[rt].l>r||tree[rt].r<l)  return 1;
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        pri=pri|tree[rt].pri;
        return tree[rt].val;
    }
    push_down(rt);
    ll ans=1;
    if(tree[rt].mid>=l) ans=ans*query(rt<<1,l,r,pri)%Mod;
    if(tree[rt].mid<r) ans=ans*query(rt<<1|1,l,r,pri)%Mod;
    push_up(rt);
    return ans;
}
char Q[20];
int main()
{
    init();
    for(int i=1;i<=tot;i++) if(prime[i]<=300) v.push_back(prime[i]);
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
    {
        ll tt=0;
        for(int j=0;j<v.size();j++) if(a[i]%v[j]==0) tt=tt|(1LL<<j);
        pp[i]=tt;
    }
    build(1,1,n);
    while(q--)
    {
        int l,r,x;
        scanf("%s",Q);
        if(Q[0]=='M')
        {
            scanf("%d%d%d",&l,&r,&x);
            ll tt=0;
            for(int i=0;i<v.size();i++) if(x%v[i]==0) tt=tt|(1LL<<i);
            update(1,l,r,x,tt);
        }
        else
        {
            ll tt=0;
            scanf("%d%d",&l,&r);
            ll ans=query(1,l,r,tt);
            for(int i=0;i<v.size();i++)
            {
                if(tt&(1LL<<i))
                {
                    ans=ans*inv_(v[i])%Mod;
                    ans=ans*(v[i]-1)%Mod;
                }
            }
            printf("%lld\n",ans);
        }
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}

