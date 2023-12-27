#include<stdio.h>

int move(int a[],int n,int m)
{
	int i;
	for(i=n-m;i<n;i++)
	{
		printf("%d ",a[i]);
	}
	for(i=0;i<n-m;i++)
	{
		printf("%d ",a[i]);
	}
	return(a[n]);
} 

int main()
{
	int x,y;
	scanf("%d",&x);
	int j,b[x];
	for(j=0;j<x;j++)
	{
		scanf("%d",&b[j]);
	}
	scanf("%d",&y);
	move(b,x,y);
	return 0;
}
