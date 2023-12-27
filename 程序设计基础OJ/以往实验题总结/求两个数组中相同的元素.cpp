#include<stdio.h>

int main()
{
	int a[6],b[8];
	int i,j;
	for(i=0;i<6;i++)
	{
		scanf("%d",&a[i]);
	}
	for(j=0;j<8;j++)
	{
		scanf("%d",&b[j]);
	}
	for(i=0;i<6;i++)
	{
		for(j=0;j<8;j++)
		{
			if(a[i]==b[j])
			{
				printf("%d\n",a[i]);
			}
		}
	} 
	return 0;
}
 
