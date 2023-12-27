#include<stdio.h>

int max(int x,int y)
{
	return(x>y?x:y);
} 

int main()
{
	int n;
	scanf("%d",&n);
	int a[n][n];
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(i=1,j=0;i<n;i++)
	{
		a[i][j]=a[i-1][j]+a[i][j];
	}
	for(i=0,j=1;j<n;j++)
	{
		a[i][j]=a[i][j-1]+a[i][j];
	} 
	for(i=1;i<n;i++)
	{
		for(j=1;j<n;j++)
		{
			a[i][j]=max(a[i-1][j],a[i][j-1])+a[i][j];
		}
	}
	printf("%d\n",a[n-1][n-1]);
	return 0;
}
