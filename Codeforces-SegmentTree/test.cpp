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
ll sum[maxn],val[maxn];
void print(ll tt[100005])
{
    for(int i=1;i<=10;i++) printf("%d ",tt[i]);
    puts("");
}
int main()
{
    //ios::sync_with_stdio(false);
    freopen("c.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    for(int i=1;i<=10;i++) val[i]=i;
    print(sum);
    print(val);

    for(int i=1;i<=6;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        for(int j=x;j<=y;j++)
        {
            sum[j]+=abs(val[j]-z);
            val[j]=z;
        }
        print(val);
        print(sum);
        printf("------------\n");
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
