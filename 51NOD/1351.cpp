#include<stdio.h>
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
struct data
{
    int low,high;
}x[maxn];
bool cmp1(const data &a,const data &b)
{
    return a.low>b.low;
}
bool cmp2(const data &a,const data &b)
{
    return a.high>b.high;
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,c,X;
        scanf("%d%d%d",&n,&c,&X);
        for(int i=1;i<=n;i++) scanf("%d%d",&x[i].low,&x[i].high);
        sort(x+1,x+1+n,cmp1);
        int ans=n;
        ll sum=0;
        for(int i=1;i<=n;i++)
        {
            sum=sum+x[i].low;
            if(sum>=X)
            {
                ans=min(ans,i);
                break;
            }
        }
      //  dbg(ans);
        sort(x+1,x+1+n,cmp2);
        sum=0;
        for(int i=n;i>=1;i--)
        {
            sum=sum+x[i].high;
            if(c-sum>=X) ans=min(ans,i-1);
        }
        printf("%d\n",ans);
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
