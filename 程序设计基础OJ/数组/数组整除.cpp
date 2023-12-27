#include<stdio.h>
int main()
{
	int a[20],i,j,b[20];
	int k=0,cnt=1;
	for(i=0;i<20;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<20;i++)
		for(j=1;j<=20;j++)
		{
			if(a[j]%a[i]==0) 
			{
				a[j]=b[k];
				k++;
			}
		}
	for(i=1;i<k;i++)
	{
		for(j=0;j<i;j++)
		{
			if(b[i]==b[j]) cnt=0;
		}
		if(cnt) printf("%d\n",b[i]);
	}
	return 0;
 } 
