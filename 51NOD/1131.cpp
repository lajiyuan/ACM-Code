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
ll solve(ll l,ll r,ll x)
{
    ll k = x/r;
    ll up = (l/(r-l))+(l%(r-l)!=0);
    ll ans=0;
    if(k>=up)
    {
        ans=ans+x-up*l+1;
        k=up-1;
    }
    else
    {
        ans = ans+max((ll)0,(x-(k+1)*l+1));
    }
    if(k==0) return ans;
    ll st = (r-l+1);
    ll en = (k*r-k*l+1);
    ans=ans+(st+en)*((en-st)/2+1)/2;
    return ans;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ll a,b,c,d;
        scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        printf("%lld\n",solve(a,b,d)-solve(a,b,c-1));
    }
    return 0;
}
