#include<stdio.h>

int judge(int m, int n)
{
	int i,j;
	int a[1000];
	int cnt;
	if(n==m) cnt=0;
	else 
	{
		int sum1=0;
		for(i=1,j=0;i<m;i++)
		{
			if(m%i==0) 
			{
				a[j]=i;
				j++;
			}
		}
		for(i=0;i<j;i++) 
		{
			sum1+=a[i];
		}
		int sum2=0;
		for(i=1,j=0;i<n;i++)
		{
			if(n%i==0)
			{
				a[j]=i;
				j++;
			}
		}
		for(i=0;i<j;i++)
		{
			sum2+=a[i];
		}

		if(sum1==n||sum2==m) cnt=1;
		else cnt=0;
	}
	return cnt;
}

int main()
{
	int m,n;
	int t,T;
	scanf("%d",&T);
	for(t=1;t<=T;t++)
	{
		scanf("%d%d",&m,&n);
		if(judge(m,n)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
