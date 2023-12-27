#include<stdio.h>
int main()
{
    int n,cnt,count=0;
    scanf("%d",&n);
    for(cnt=1;cnt<=n;cnt++)
    {
        int a[10];
        int i;
        for(i=0;i<10;i++)
        {
            count=0;
            scanf("%d",&a[i]);
        }
        for(i=0;i<10;i++)
        {
            if(a[i]<0) count++; 
        }
        printf("%d\n",count);
    }
    return 0;
 }
