#include<stdio.h>
int main()
{
    int n,cnt;
    scanf("%d",&n);
    for(cnt=1;cnt<=n;cnt++)
    {
        int a[10];
        int i,x,num=0;
        for(i=0;i<10;i++)
        {
            scanf("%d",&a[i]);
        }
            scanf("%d",&x);
            for(i=0;i<10;i++)
            {
                if(x==a[i]){
                    num=i;
                    break;
                }   
            }
            if(i<=9) printf("%d\n",num);
            else printf("Not found\n");
    }
    return 0;
}
