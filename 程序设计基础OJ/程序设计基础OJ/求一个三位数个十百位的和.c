#include<stdio.h>
int main()
{
	int a,b,c,d,sum;
	scanf("%d",&a);
	b=(int)(a/100);
	c=(int)((a%100)/10);
	d=(int)((a%100)%10);
	sum=b+c+d;
	printf("%d\n",sum);
	return 0;
 } 
