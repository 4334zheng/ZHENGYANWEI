#include<stdio.h>
int main()
{
	int a,b,c,d;
	scanf("%d",&a);
	b=a%10;
	c=a%100/10;
	d=a/100;
	if(a>=100&&a<=999)
	{
		if(a==b*b*b+c*c*c+d*d*d)
		{
			printf("1\n");
		}
		else
		{
			printf("0\n");
		}
	}
	else
	{
		printf("ERROR\n");
	}
	return 0;
} 
