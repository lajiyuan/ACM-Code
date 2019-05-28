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
ll hash_[2][maxn],xp[2][maxn];
const int Mod1 = 1000000007;
const int Mod2 = 19260817;
void init()
{
    xp[0][0]=1;
    for(int i=1;i<maxn;i++)
        xp[0][i]=xp[0][i-1]*13331%Mod1;
    xp[1][0]=1;
    for(int i=1;i<maxn;i++)
        xp[1][i]=xp[1][i-1]*1331%Mod2;
    return ;
}
void make_hash(char str[])
{
    int len=strlen(str);
    hash_[0][len]=0;
    hash_[1][len]=0;
    for(int i=len-1;i>=0;i--)
    {
        hash_[0][i]=(hash_[0][i+1]*13331%Mod1+str[i]-'A'+1)%Mod1;
        hash_[1][i]=(hash_[1][i+1]*1331%Mod2+str[i]-'A'+1)%Mod2;
    }
    return ;
}
pll Get_hash(int i,int L)//得到起点为i，长度为L的子串的hash值
{
    return pll((hash_[0][i]-hash_[0][i+L]*xp[0][L]%Mod1+Mod1)%Mod1,(hash_[1][i]-hash_[1][i+L]*xp[1][L]%Mod2+Mod2)%Mod2);
}
char str[maxn];
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    scanf("%s",str);
    init();
    make_hash(str);
    int m;
    scanf("%d",&m);
    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        int l=0,r=n-max(a,b);
        while(l<=r)
        {
            int mid=l+r>>1;
            if(Get_hash(a,mid)==Get_hash(b,mid)) l=mid+1;
            else r=mid-1;
        }
        printf("%d\n",r);
    }
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
