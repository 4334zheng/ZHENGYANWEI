#include<stdio.h>
#include<string.h>
int func_de(int a,int b[4])
{
    b[0]=a/1000;
    b[1]=a%1000/100;
    b[2]=a%100/10;
    b[3]=a%10;
}
int main()
{
    int n,i;
    int b[4];
    scanf("%d",&n);
    func_de(n,b);
    for(i=0;i<4;i++)
    {
        printf("%d ",b[i]);
    }
    return 0;
}
