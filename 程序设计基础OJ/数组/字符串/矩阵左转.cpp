#include<stdio.h>
int main()
{
	int T,t;
	scanf("%d",&T);
	for(t=1;t<=T;t++)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		int a[m][n];
		int i,j;
		for(j=0;j<n;j++)
		{
			for(i=m-1;i>=0;i--)
			{
				scanf("%d",&a[i][j]);
			}
		}
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				if(j<n-1) printf("%d ",a[i][j]);
				else printf("%d",a[i][j]);
			}
			printf("\n");
		} 
	}
	return 0;
}
