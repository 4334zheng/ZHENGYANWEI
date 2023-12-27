#include<stdio.h>
int main()
{
	int a,b,c,d,e;
	scanf("%d",&a);
	b=(int)(a/100);
	c=(int)((a%100)/10);
	d=(int)((a%100)%10);
	e=d*100+c*10+b;
	printf("%d\n",e);
	return 0;
}
