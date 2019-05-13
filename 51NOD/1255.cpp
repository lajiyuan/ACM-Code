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
char str[maxn];
int sum[30];
int vis[30];
int la[30];
int nex[maxn][30];
int pos[30];
int main()
{
    //ios::sync_with_stdio(false);
    //freopen("a.txt","r",stdin);
    //freopen("b.txt","w",stdout);
    scanf("%s",str);
    int len=strlen(str);
    for(int i=0;i<len;i++) sum[str[i]-'a']++;
    memset(nex,-1,sizeof(nex));
    memset(pos,-1,sizeof(pos));
    for(int i=len-1;i>=0;i--)
    {
        pos[str[i]-'a']=i;
        for(int j=0;j<26;j++) nex[i][j]=pos[j];
    }
    vector<char> tt;
    for(int i=0;i<26;i++) if(sum[i]>0) tt.push_back(char(i+'a'));
    int sz=tt.size();
    int pos=0;
    int now=0;
    memset(la,-1,sizeof(la));
    vector<char> ans;
    for(int i=0;i<len;i++)
    {
        if(vis[str[i]-'a']) continue;
        if(str[i]==tt[pos])
        {
            vis[str[i]-'a']=1;
            now=i;
            ans.push_back(str[i]);
            memset(la,-1,sizeof(la));
            while(vis[tt[pos]-'a'])
            {
                pos++;
                if(pos==sz) break;
            }
            if(pos==sz) break;
        }
        else
        {
            if(sum[str[i]-'a']==1)
            {
                vis[str[i]-'a']=1;
                int pre=now;
                int flag=0;
                for(int j=0;j<(str[i]-'a');j++)
                {
                    if(nex[pre][j]!=-1&&!vis[j])
                    {
                       // dbg2(j,nex[pre][j]);
                        if(nex[pre][j]<i)
                        {
                            flag=1;
                            vis[j]=1;
                            pre=nex[pre][j];
                            ans.push_back(char(j+'a'));
                        }
                    }
                }
                if(flag==0)
                {
                    if(la[str[i]-'a']==-1)
                    {
                        ans.push_back(str[i]);
                        now=i;
                        memset(la,-1,sizeof(la));
                    }
                    else
                    {
                        ans.push_back(str[i]);
                        now=la[str[i]-'a'];
                        memset(la,-1,sizeof(la));
                    }
                }
                else
                {
                    ans.push_back(str[i]);
                    now=i;
                    memset(la,-1,sizeof(la));
                }

            }
            else
            {
                sum[str[i]-'a']--;
                if(la[str[i]-'a']==-1) la[str[i]-'a']=i;
            }
        }
    }
    for(int i=0;i<ans.size();i++) printf("%c",ans[i]);
    //cout << "time: " << (long long)clock() * 1000 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
