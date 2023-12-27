#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	int i;
	int x,sum=0;
	
	for(x=0;x<n;x++)
	{
		for(i=0;i<sum;i++)printf(" ");
		for(i=0;i<n;i++)
		{
			printf("#");
		}
		sum++;
		printf("\n");
	}
	
	return 0;
 } 
