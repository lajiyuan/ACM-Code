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

const int maxn = 5005;
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
char Ma[maxn*2];
int Mp[maxn*2];//Mp[i]-1为该点为中心的最长回文子串长度
void Manacher(char s[],int len)
{
    int l=0;
    Ma[l++]='$';
    Ma[l++]='#';
    for(int i=0; i<len; i++)
    {
        Ma[l++]=s[i];
        Ma[l++]='#';
    }
    Ma[l]=0;
    int mx=0,id=0;
    for(int i=0; i<l; i++)
    {
        Mp[i]=mx>i?min(Mp[2*id-i],mx-i):1;
        while(Ma[i+Mp[i]]==Ma[i-Mp[i]]) Mp[i]++;
        if(i+Mp[i]>mx)
        {
            mx=i+Mp[i];
            id=i;
        }
    }
}
/*
str:   abaaba

i:     0 1 2 3 4 5 6 7 8 9 10 11 12 13

Ma[i]: $ # a # b # a # a $  b #  a  #

Mp[i]: 1 1 2 1 4 1 2 7 2 1  4 1  2  1

*/

char s[maxn];
vector<int> v[maxn];
int dp[maxn];
int main()
{
    scanf("%s",s);
    int len=strlen(s);
    Manacher(s,len);
    int ans=0;
    for(int i=1; i<2*len+2; i++)
    {
        if(i%2==1)
        {
            for(int j=i/2,k=2;j<=i/2+Mp[i]/2-1;j++,k+=2)
            {
                v[j].push_back(k);
            }
        }
        else
        {
            for(int j=i/2-1,k=1;j<=i/2-1+Mp[i]/2-1;j++,k+=2)
            {
                v[j].push_back(k);
            }
        }
    }
    memset(dp,INF,sizeof(dp));
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<v[i].size();j++)
        {
            if(i+1==v[i][j]) dp[i]=1;
            if(i+1>v[i][j]) dp[i]=min(dp[i],dp[i-v[i][j]]+1);
        }
    }
    printf("%d\n",dp[len-1]);
    return 0;
 }
