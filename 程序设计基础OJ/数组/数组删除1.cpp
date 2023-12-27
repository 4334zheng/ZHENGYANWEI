#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	int j;
	for(j=1;j<=n;j++)
	{
		int a[10];
		int i,cnt=1;
		for(i=0;i<10;i++)
		{
			scanf("%d",&a[i]);
		}
		int x,count=0;
		scanf("%d",&x);
		for(i=0;i<10;i++)
		{
			if(x!=a[i]) count++;
		}
		for(i=0;i<10;i++)
		{
			if(count==10)
			{
		   		printf("Not found\n");break;
			}
	   		if(x!=a[i])
		    {
				if(cnt<count) printf("%d ",a[i]),cnt++;
			    else printf("%d\n",a[i]);
		    }
	   
		}
	}
	return 0;
}
