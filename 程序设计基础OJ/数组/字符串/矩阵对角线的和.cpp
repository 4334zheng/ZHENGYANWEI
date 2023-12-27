#include<stdio.h>
int main()
{
    int T,t;
    scanf("%d",&T);
    for(t=1;t<=T;t++)
    {
        int n,i,j;
        int sum1=0,sum2=0,sum=0;
        scanf("%d",&n);
        int a[n][n];
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                scanf("%d",&a[i][j]);
            }
            if(i<n-1) scanf("\n");
        }
        for(i=0,j=0;i<n;i++,j++)
        {
            sum1+=a[i][j];
        }
        for(i=n-1,j=0;i>=0;i--,j++)
        {
            sum2+=a[i][j];
        } 
        sum=sum1+sum2;
        if(n%2==0) printf("%d\n",sum);
        else
        {
            int m=(n-1)/2;
            sum=sum-a[m][m];
            printf("%d\n",sum);
        }
    }
    return 0; 
}
