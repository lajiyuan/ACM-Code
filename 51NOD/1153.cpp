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
//返回下标的st表
int rmq[maxn],mm[maxn],st[22][maxn];
void init_rmq(int n)
{
    mm[0]=-1;
    for(int i=1; i<=n; i++) mm[i]=((i&i-1))==0?mm[i-1]+1:mm[i-1];//mm[i]=log2(i)+1更新完成
    for(int i=1; i<=n; i++) st[0][i]=i;//第I位起往右走2^0位的区间的最小值的下标就是其自身
    for(int i=1; i<=mm[n]; i++) //枚举深度
    {
        for(int j=1; j+(1<<i)-1<=n; j++) //枚举左界j，区间长(1<<i)故往右走(1<<i)-1步是右界，右界不超N则执行
        {
            int a=st[i-1][j];//读出左半区间最小值的下标
            int b=st[i-1][j+(1<<(i-1))];//读出右半区间最小值的下标
            if(rmq[a]>rmq[b]) st[i][j]=a;//比较两个下标对应的值，a位的值小则st[i][j]记为a
            else st[i][j]=b;//b位的值小则st[i][j]记为b
        }
    }
}
int ask_rmq(int a,int b) //查找区间A到B的较大值的下标
{
    int t=mm[b-a+1];//得区间对应ST表深度
    b-=(1<<t)-1;//右边区间的左界
    a=st[t][a];//读出左半（可以大于一半）区间的最小值下标
    b=st[t][b];//读出右半（可以大于一半）区间的最小值下标
    return rmq[a]>rmq[b]?a:b;//返回两个位置上值小那个下标
}
int dfs(int l,int r)
{
  //  dbg2(l,r);
    if(l==r) return 1;
    if(l>r) return 0;
    int pos=ask_rmq(l,r);
   // dbg(pos);
    return max(dfs(l,pos-1),dfs(pos+1,r))+1;
}
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&rmq[i]);
    init_rmq(n);
    printf("%d\n",dfs(1,n));
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
