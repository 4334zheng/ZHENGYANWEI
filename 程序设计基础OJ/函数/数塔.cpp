#include<stdio.h>
#define N 100

int max(int x,int y)
{
	return(x>=y?x:y); 
}

int GetMaxSum(int num[][N],int n) 
{
	int i,j;
	int sum=0;
	for(i=n-1;i>=0;i--)
	{
		for(j=0;j<i;j++)
		{
			num[i-1][j]=max(num[i][j]+num[i-1][j],num[i][j+1]+num[i-1][j]);
		}
	}
	sum=num[0][0];
	return(sum);
}

int main()
{
	int t,T;
	scanf("%d",&T);
	for(t=1;t<=T;t++)
	{
		int n;
		scanf("%d",&n);
		int a[100][N]; 
		int k,l;
		for(k=0;k<n;k++)
		{
			for(l=0;l<=k;l++)
			scanf("%d",&a[k][l]);
		}
		printf("%d\n",GetMaxSum(a,n));
	}
	return 0;
}
