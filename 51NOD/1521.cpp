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
int p[maxn];
int tmp[maxn];
int n,k,a;
bool check(int mid)
{
    for(int i=1;i<=n;i++) tmp[i]=0;
    for(int i=1;i<=mid;i++) tmp[p[i]]=1;
    int res=0;
    for(int i=1;i<=n;i++)
    {
        if(tmp[i]==0)
        {
            int cnt=0;
            while(i<=n&&tmp[i]==0)
            {
                cnt++;
                i++;
            }
            res+=(cnt+1)/(a+1);
        }
    }
    return res>=k;
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    scanf("%d%d%d",&n,&k,&a);
    int m;
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",&p[i]);
    int l=0,r=m;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid)) l=mid+1;
        else r=mid-1;
    }
    if(r==m) printf("-1\n");
    else printf("%d\n",r+1);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
