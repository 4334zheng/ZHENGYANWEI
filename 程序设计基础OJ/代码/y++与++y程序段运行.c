#include<stdio.h>
int main()
{
	int x,y;
	x=y=0;
	while(x<15) y++,x+=++y;
	printf("%d,%d\n",y,x);
 } 
