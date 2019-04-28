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
long long Fac[maxn],Inv[maxn],inv[maxn];
void init()
{
    Fac[0]=Inv[0]=Fac[1]=Inv[1]=inv[1]=1;
    for(int i=2;i<maxn;i++)
    {
        Fac[i]=Fac[i-1]*i%Mod;
        inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
        Inv[i]=Inv[i-1]*inv[i]%Mod;
    }
}
long long c(int n,int m)
{
    if(n<m||m<0) return 0;
    return Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    init();
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        ll ans=0;
        for(int i=1;i<=min(n,m)-1;i++) ans=(ans+c(n-2,i-1)*c(m-2,i-1)%Mod)%Mod;
        printf("%lld\n",ans);
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
