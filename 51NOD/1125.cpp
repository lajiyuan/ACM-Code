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
map<int,int> mp;
int to[maxn],a[maxn],b[maxn],vis[maxn];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) b[i]=a[i];
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++) mp[b[i]]=i;
    for(int i=1;i<=n;i++) to[i]=mp[a[i]];
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            int tt=i;
            ll res1=a[tt];
            int minn=a[tt];
            vis[i]=1;
            int cnt=0;
            while(to[tt]!=i)
            {
                tt=to[tt];
                vis[tt]=1;
                cnt++;
                minn=min(minn,a[tt]);
                res1+=a[tt];
            }
            res1-=minn;
            if(minn==b[1])
            {
                ans=ans+res1+1LL*cnt*minn;
                continue;
            }
            else
            {
                ll res2=res1+1LL*b[1]*cnt+2LL*(b[1]+minn);
                ans=ans+min(res2,res1+1LL*cnt*minn);
            }
        }
    }
    printf("%lld\n",ans);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
