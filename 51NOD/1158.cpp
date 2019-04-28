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

const int maxn = 505;
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
int a[maxn][maxn];
int sum[maxn][maxn];
int pre[maxn],nex[maxn];
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(a[j][i]==1) sum[j][i]=sum[j-1][i]+1;
            else sum[j][i]=0;
        }
    }

//    for(int i=1;i<=n;i++)
//    {
//        for(int j=1;j<=m;j++)
//        {
//            dbg3(i,j,sum[i][j]);
//        }
//    }
    stack<int> s;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        while(!s.empty()) s.pop();
        for(int j=1;j<=m;j++)
        {
            while(!s.empty()&&sum[i][s.top()]>=sum[i][j]) s.pop();
            if(s.empty()) pre[j]=1;
            else pre[j]=s.top()+1;
            s.push(j);
        }
        while(!s.empty()) s.pop();

        for(int j=m;j>=1;j--)
        {
            while(!s.empty()&&sum[i][s.top()]>=sum[i][j]) s.pop();
            if(s.empty()) nex[j]=m;
            else nex[j]=s.top()-1;
            s.push(j);
        }
      //  for(int j=1;j<=n;j++) dbg3(j,pre[j],nex[j]);
        for(int j=1;j<=n;j++) ans=max(ans,sum[i][j]*(nex[j]-pre[j]+1));
    }
    printf("%d\n",ans);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
