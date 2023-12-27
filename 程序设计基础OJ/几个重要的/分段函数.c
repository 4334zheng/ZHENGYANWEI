#include<stdio.h>
int main()
{
	int x,y;
	scanf("%d",&x);
	if(x<1) y=x;
	if(1<=x<10) 
	{
		y=2*x-1;
		if(y<14) y=y-5;
		else y=y;
	 } 
	if(x>=10)
	{
		y=3*x-11;
		if(y<25) y=y*2;
		else y=y;
	}
	printf("%d\n",y);
	return 0;
 } 
