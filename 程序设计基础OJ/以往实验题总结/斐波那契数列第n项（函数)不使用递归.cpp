#include<stdio.h>

int fact(int n)
{
	int a[n];
	int i;
	a[0]=0;
	a[1]=1;
	for(i=2;i<=n;i++)
	{
		a[i]=a[i-1]+a[i-2];
	} 
	return a[n];
}

int main()
{
	int n;
	scanf("%d",&n);
	printf("%d\n",fact(n));
	return 0;
}
