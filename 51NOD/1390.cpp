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
bool sqr(ll x)
{
    int t=sqrt(x);
    if(1LL*t*t==x) return true;
    return false;
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    ll a,b;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld%lld",&a,&b);
        if(!sqr(a+b))
        {
            printf("-1\n");
            continue;
        }
        ll x=2LL*(ll)sqrt(a+b)-1;
        int ans=0;
        while(a>0&&x>0)
        {
          //  dbg2(a,x);
            if(a>=x&&a-x!=2)
            {
                a-=x;
                ans++;
            }
            x-=2;
        }
        if(a!=0) printf("-1\n");
        else printf("%d\n",ans);
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
