#include<stdio.h>

int move(int a[],int n,int m)
{
	int i,j;
	int b[n]; 
	for(i=n-m,j=0;i<n;i++,j++)
	{
		b[j]=a[i];
	}
	for(i=n-m-1;i>=0;i--)
	{
		a[i+m]=a[i];
	}
	for(i=0;i<j;i++)
	{
		a[i]=b[i];
	}
	for(i=0;i<n;i++)
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
