#include<stdio.h>

int a[100],b[100];
int cnt=0,cnt1,n,k;
int judge(int a[],int i,int sum,int end)
{
	cnt++;
	if(i==n) return(sum==end);
	else
	{
		if(judge(a,i+1,sum,end))
		{
			return 1;
		}
		else if(judge(a,i+1,sum+a[i],end))
		{
			b[cnt1++]=a[i];
			return 1;
		}
	}
} 

int main()
{
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		cnt1=0;
		int i;
		for(i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
		} 
		if(judge(a,0,0,k))
		{
			printf("YES\n");
			for(i=cnt1-1;i>=0;i--)
			{
				if(i==cnt1-1)
					printf("%d",b[i]);
				else
					printf(" %d",b[i]);
			}
			printf("\n");
		} 
		else printf("NO\n");
	}
	return 0;
}
