#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 2e5+5;
struct T
{
    int l,r,mid;
    int val,id;
}tree[maxn<<2];
void push_up(int rt)
{
    tree[rt].val=max(tree[rt<<1].val,tree[rt<<1|1].val);
}
void build(int rt ,int l,int r)
{
    tree[rt].l=l;
    tree[rt].r=r;
    if(l==r)
    {
        tree[rt].id=-1;
        tree[rt].val=0;
        return ;
    }
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    push_up(rt);
}
void update(int rt,int pos,int val,int id)
{
    if(tree[rt].l==tree[rt].r)
    {
        tree[rt].val=max(tree[rt].val,val);
        tree[rt].id=id;
        return ;
    }
    if(pos<=tree[rt].mid) update(rt<<1,pos,val,id);
    else update(rt<<1|1,pos,val,id);
    push_up(rt);
}
int query(int rt,int val,int l,int r)
{
    if(tree[rt].l>=l&&tree[rt].r<=r)
    {
        if(tree[rt].val<val) return -1;
    }
    if(tree[rt].l==tree[rt].r) return tree[rt].id;
    int ans=-1;
    if(tree[rt].mid>=l)
    {
        ans=query(rt<<1,val,l,r);
        if(ans!=-1) return ans;
    }
    if(tree[rt].id<r)
    {
        ans=query(rt<<1|1,val,l,r);
        if(ans!=-1) return ans;
    }
    return -1;
}
struct Bus
{
    int l,r,t,id;
    bool operator<(const Bus y)const
    {
        if(l==y.l) return id<y.id;
        return l<y.l;
    }
}bus[maxn<<2];
int Hash[maxn<<2],cnt;
int ans[maxn<<2];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+m;i++)
    {
        scanf("%d%d%d",&bus[i].l,&bus[i].r,&bus[i].t);
        bus[i].id=i;
        Hash[++cnt]=bus[i].t;
    }
    sort(bus+1,bus+1+n+m);
    sort(Hash+1,Hash+1+cnt);
    build(1,1,cnt);
    int d=unique(Hash+1,Hash+1+cnt)-Hash-1;
    for(int i=1;i<=n+m;i++)
    {
        int pos=lower_bound(Hash+1,Hash+1+d,bus[i].t)-Hash;
        if(bus[i].id<=n) update(1,pos,bus[i].r,bus[i].id);
        else ans[bus[i].id-n]=query(1,bus[i].r,pos,cnt);
    }
    for(int i=1;i<=m;i++) printf("%d ",ans[i]);
    return 0;
}
