#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
const double eps = 1e-8;
int sgn(double x)
{
    if(fabs(x)<eps) return 0;
    if(x<0) return -1;
    return 1;
}
int main()
{
    int t;
    scanf("%d",&t);
    int cas=0;
    while(t--)
    {
        int n;
        int ans=1;
        scanf("%d",&n);
        double tmp=0;
        double cc=0;
        for(int i=2;;i++)
        {
            tmp=(1.0-cc)*(1.0*(i-1)/n);
            cc=cc+tmp;
            if(sgn(cc-0.5)>=0)
            {
                ans=i;
                break;
            }
        }
        printf("Case %d: %d\n",++cas,ans-1);
    }
    return 0;
}
