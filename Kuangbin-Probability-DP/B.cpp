#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1e5+5;
double a[maxn];
int main()
{
    int t;
    int tt=0;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%lf",&a[i]);
        for(int i=n-1;i>=1;i--)
        {
            double tmp=0.0;
            int cnt=0;
            for(int j=1;j<=6;j++)
            {
                if(i+j<=n)
                {
                    cnt++;
                    tmp+=a[i+j];
                }
            }
            a[i]+=tmp/cnt;
        }
        printf("Case %d: %.10f\n",++tt,a[1]);
    }
    return 0;
}
