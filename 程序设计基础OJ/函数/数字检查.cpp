#include<stdio.h>
 
int search(int x)
{
    int a,b,c,d;
    int cnt=0;
    a=x/1000;
    b=x%1000/100;
    c=x%100/10;
    d=x%10;
    if(a%2==0&&b%2==0&&c%2==0&&d%2==0) cnt=1;
    else cnt=0;
    return cnt;
}
 
int main()
{
    int n,k=0;
    int num=0;
    int a[100];
    while(1)
    {
        scanf("%d",&n);
        if(n==-1) break;
        else if(search(n))
        {
            a[k]=n;
            k++;
            num++; 
        }
    }
    printf("%d\n",num);
    int i,j,t;
    for(i=0;i<k;i++){
        for(j=0;j<k-1;j++)
        {
            if(a[j]>a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    for(i=0;i<k;i++)
        printf("%.4d\n",a[i]);
    return 0;
}
