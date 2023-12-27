#include<stdio.h>

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	int a[n][m],b[n][m];
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&b[i][j]);
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m-1;j++)
		{
			printf("%d ",a[i][j]+b[i][j]);
		}
		printf("%d",a[i][m-1]+b[i][m-1]);
		printf("\n");
	}
	return 0;
}
