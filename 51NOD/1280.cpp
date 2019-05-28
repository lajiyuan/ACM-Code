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
int a[maxn];
set<int> s1,s2;
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int pos2=n;
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        s1.insert(a[i]);
        if(!s2.count(a[i]))
        {
            while(!s2.count(a[i]))
            {
                s2.insert(a[pos2]);
                pos2--;
            }
            pos2++;
        }
        if(s1.size()==s2.size())
        {
            int l=i;
            while(s2.count(a[l+1])&&l<n) l++;
            int r=pos2-1;
            while(s1.count(a[r])&&r>=1) r--;
            r++;
            ans=ans+1LL*(l-i+1)*(pos2-r+1);
            i=l;
            pos2=r;
        }
    }
    printf("%lld\n",ans);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
