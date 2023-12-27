#include<stdio.h>

int main()
{
	int n;
	scanf("%d",&n);
	int i,j;
	int sum=0;
	for(j=1;j<=n;j++)
	{
		int sum1=1;
		for(i=1;i<=j;i++)
		{
			sum1*=i;
		}
		sum+=sum1;
	}
	printf("%ld\n",sum);
	return 0;
}
