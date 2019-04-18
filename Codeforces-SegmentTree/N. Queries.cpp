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
const int Mod=4001;
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

struct Ans
{
    int pre1,suf1;
    int sum1,len;
    int ans;
    Ans(){}
    Ans(int p1,int s1,int sum,int an,int l)
    {
        pre1=p1;
        suf1=s1;
        sum1=sum;
        ans=an;
        len = l;
    }
     Ans operator + (const Ans &B) const
     {
         Ans res;

         int tmp=ans+B.ans;
         tmp = tmp +pre1*(B.len-B.suf1);
         tmp = tmp +(len-pre1) *B.suf1;
         res.ans=tmp%Mod;

         if(B.sum1&1) res.pre1 = len-pre1+B.pre1;
         else res.pre1 = pre1+B.pre1;

         if(sum1&1) res.suf1 = suf1+B.len-B.suf1;
         else res.suf1 = suf1+B.suf1;

         res.sum1 = sum1+B.sum1;
         res.len = len+B.len;

         return res;
     }
     void print()
     {
         printf("pre1 = %d,suf1 = %d,sum1 = %d,ans = %d\n",pre1,suf1,sum1,ans);
     }
};
struct T
{
    int l,r,mid;
    Ans val;
}tree[10][maxn<<2];
int a[maxn];
int b[10][maxn];
void push_up(int flag,int rt)
{
    tree[flag][rt].val=tree[flag][rt<<1].val+tree[flag][rt<<1|1].val;
}
void build(int flag,int rt,int l,int r)
{
    tree[flag][rt].l=l;p
    tree[flag][rt].r=r;
    if(l==r)
    {
        Ans tt;
        tt.pre1=b[flag][l];
        tt.suf1=b[flag][l];
        tt.ans=tt.pre1;
        tt.len=1;
        tt.sum1=tt.pre1;
        tree[flag][rt].val=tt;
        return ;
    }
    int mid=tree[flag][rt].mid=l+r>>1;
    build(flag,rt<<1,l,mid);
    build(flag,rt<<1|1,mid+1,r);
    push_up(flag,rt);
}
void update(int flag,int rt,int pos,int val)
{
   if(tree[flag][rt].l==tree[flag][rt].r)
   {
       Ans tt;
       tt.pre1=val;
       tt.suf1=val;
       tt.ans=val;
       tt.len=1;
       tt.sum1=val;
       tree[flag][rt].val=tt;
       return ;
   }
   if(pos<=tree[flag][rt].mid) update(flag,rt<<1,pos,val);
   else update(flag,rt<<1|1,pos,val);
   push_up(flag,rt);
}
Ans query(int flag,int rt,int l,int r)
{
    if(tree[flag][rt].l>r||tree[flag][rt].r<l) return Ans(0,0,0,0,0);
    if(tree[flag][rt].l>=l&&tree[flag][rt].r<=r) return tree[flag][rt].val;
    Ans ans=Ans(0,0,0,0,0);
    if(tree[flag][rt].mid>=l) ans=ans+query(flag,rt<<1,l,r);
    if(tree[flag][rt].mid<r) ans=ans+query(flag,rt<<1|1,l,r);
    return ans;
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(a[i]&(1<<j)) b[j][i]=1;
            else b[j][i]=0;
        }
    }
    for(int i=0;i<10;i++)  build(i,1,1,n);
    while(q--)
    {
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==1)
        {
            for(int i=0;i<10;i++)
            {
                if(y&(1<<i)) update(i,1,x,1);
                else update(i,1,x,0);
            }
        }
        else
        {
            int res=0;
            for(int i=0;i<10;i++) res=(res+(1<<i)*query(i,1,x,y).ans%Mod)%Mod;
            printf("%d\n",res);
        }
    }
    return 0;
}
