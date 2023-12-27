#include<stdio.h>

int max(int a, int b)
{
	return(a>b?a:b);
}

int main()
{
	int a=5;
	int b=6;
	int c;
	c=max(10,20);
	c=max(a,b);
	c=max(23,43);
	printf("%d",max(a,b));
	return 0;
}
