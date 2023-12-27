#include<stdio.h>

int OnBus(int a,int n,int y)
{
	if(n==1||n==3) return a; 
	else if(n==2) return 0;
	else if(n==4) return y;
	else if(n>=5) return(OnBus(a,n-1,y)+OnBus(a,n-2,y));
}

int main()
{
	int a,n,m,x,y;
	scanf("%d%d%d%d",&a,&n,&m,&x);
	int sum=0;
	int i,j;
	for(y=0;;y++)
	{
		sum=0;
		for(i=1;i<n;i++)
		{
			sum+=OnBus(a,i,y);
		}
		if(sum==m) break;
	}
	sum=0;
	for(i=1;i<=x;i++)
	{
		sum+=OnBus(a,i,y);
	}
	printf("%d\n",sum);
	return 0;
}
