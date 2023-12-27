#include<stdio.h>

float fact(int m, int n)
{
	float sum1=1,sum2=1;
	int i,j;
	for(i=1;i<=m;i++)
	{
		sum1*=i;
	}
	for(j=1;j<=n;j++)
	{
		sum2*=j;
	}
	float sum3=1;
	for(i=1;i<=m-n;i++)
	{
		sum3*=i;
	}
	float sum;
	sum=sum1/(sum2*sum3);
	return sum;
} 

int main()
{
	int m,n;
	scanf("%d %d",&m,&n);
	printf("%.0f\n",fact(m,n));
	return 0;
}
