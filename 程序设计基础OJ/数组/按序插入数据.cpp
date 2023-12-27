#include<stdio.h>
int main()
{
    int t,cnt;
    scanf("%d",&t);
    for(cnt=1;cnt<=t;cnt++)
    {
        int n,i;
        scanf("%d",&n);
        int a[n+1];
        for(i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        int x,num;
        scanf("%d",&x);
        if(a[1]>a[0])
        {
            for(i=0;i<n;i++)
            {
                if(x<a[i]){
                    num=i;
                    break;
                }
            }
            for(i=n-1;i>=num;i--)
            {
                a[i+1]=a[i];
            }
            a[num]=x;
        }
        else
        {
            for(i=0;i<n;i++)
            {
                if(x>a[i]){
                    num=i;
                    break;
                }
            }
            for(i=n-1;i>=num;i--)
            {
                a[i+1]=a[i];
            } 
            a[num]=x;
        }
        for(i=0;i<n;i++){
            printf("%d ",a[i]);
        }
        printf("%d\n", a[n]);
    }
    return 0;
}
