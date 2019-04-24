#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e5+5;
int a[maxn];
int main()
{
    int t;
    scanf("%d",&t);
    int cnt=0;
    while(t--)
    {
        int n;
        scanf("%d",&n);
        ll ans=0;
        ll cc=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            ans=ans+abs(a[i]);
            if(a[i]>0) cc++;
        }
        if(cc==0) printf("Case %d: inf\n",++cnt);
        else printf("Case %d: %lld/%lld\n",++cnt,ans/__gcd(ans,cc),cc/__gcd(ans,cc));
    }
    return 0;
}
