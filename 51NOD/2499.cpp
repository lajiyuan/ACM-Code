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
int dp[12][12];
int a[12];
int pre[12][12];
int ans[12];
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    int cnt=0;
    int num=n;
    while(num!=0)
    {
        cnt++;
        a[cnt]=(num%10);
        num/=10;
    }
    for(int i=cnt-1;i>=1;i--)
    {
        if(a[i]<a[i+1])
        {
            int pos=i+1;
            for(int j=i+1;j<=cnt;j++)
            {
                if(a[j]!=a[i+1]) break;
                pos=j;
            }
            a[pos]--;
            for(int j=pos-1;j>=1;j--) a[j]=9;
        }
    }
    for(int i=cnt;i>=1;i--) printf("%d",a[i]);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
