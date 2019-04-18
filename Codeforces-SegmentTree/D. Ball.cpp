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

const int maxn = 5e5+5;
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
    int val;
}tree[maxn<<2];
void push_up(int rt)
{
    tree[rt].val=max(tree[rt<<1].val,tree[rt<<1|1].val);
}
void build(int rt,int l,int r)
{
    tree[rt].val=-1;
    tree[rt].l=l;
    tree[rt].r=r;
    if(l==r) return ;
    int mid=tree[rt].mid=l+r>>1;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    push_up(rt);
    return ;
}
void update(int rt,int pos,int val)
{
    if(tree[rt].l==tree[rt].r)
    {
        tree[rt].val=max(tree[rt].val,val);
        return;
    }
    if(tree[rt].mid>=pos) update(rt<<1,pos,val);
    else update(rt<<1|1,pos,val);
    push_up(rt);
    return ;
}
int query(int rt,int l,int r)
{
    if(tree[rt].l>r||tree[rt].r<l) return -1;
    if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].val;
    int ans=-1;
    if(tree[rt].mid>=l) ans=max(ans,query(rt<<1,l,r));
    if(tree[rt].mid<r) ans=max(ans,query(rt<<1|1,l,r));
    return ans;
}
struct data
{
    int b,i,r;
    void output()
    {
        dbg3(b,i,r);
    }
}x[maxn];
bool cmp(const data &a,const data &b)
{
    if(a.b==b.b)
    {
        if(a.i==b.i) return a.r>b.r;
        else return a.i>b.i;
    }
    return a.b>b.b;
}
int a[maxn];//ԭ����
int b[maxn];//ÿ��λ����ɢ���ֵ
int c[maxn];//c[i]��ʾ��ɢ��Ϊi��ԭ����ֵΪc[i]
int d;
int Hash[maxn];//hashȥ������
void GetHash(int a[],int n)
{
    for(int i=1;i<=n;i++) Hash[i]=a[i];
    sort(Hash+1,Hash+1+n);
    d=unique(Hash+1,Hash+1+n)-Hash-1;
    for(int i=1;i<=n;i++)
    {
        b[i]=lower_bound(Hash+1,Hash+1+d,a[i])-Hash;
        c[b[i]]=a[i];
    }
}
vector<pii> tt;
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&x[i].b);
    for(int i=1;i<=n;i++) scanf("%d",&x[i].i);
    for(int i=1;i<=n;i++) scanf("%d",&x[i].r);
    for(int i=1;i<=n;i++) a[i]=x[i].i;
    GetHash(a,n);
    build(1,1,d);
    for(int i=1;i<=n;i++) x[i].i=b[i];
    sort(x+1,x+1+n,cmp);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(i>1&&x[i].b!=x[i-1].b)
        {
            for(int i=0;i<tt.size();i++) update(1,tt[i].Fi,tt[i].Se);
            tt.clear();
        }
        int tmp = query(1,x[i].i+1,d);
        if(tmp>x[i].r) ans++;
        tt.pb(pii(x[i].i,x[i].r));
    }
    printf("%d\n",ans);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}

