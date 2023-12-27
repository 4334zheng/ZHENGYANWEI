#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	int a[2][n+1];
	int i,b=0,cnt=1;
	for(i=0;i<=n;i++)
	{
		a[0][i]=i;
		a[1][i]=0;	
	} 
	while(cnt!=n+1)
	{
		for(i=1;i<=n;i++)
		{
			if(a[1][i]==0&&(++b%3)==0) a[1][i]=cnt++;
		}
		
	}
	for(i=1;i<=n;i++)
	{
		for(b=0;b<=n;b++)
		{
			if(a[1][b]==i) printf("%d",a[0][b]);
		}
		if(i<=n-1) printf(" ");
		if(i==n-1) printf("\n");
	}
	
	return 0;
} 
