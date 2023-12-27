#include<stdio.h>
int main()
{
	int a,b,sum;
	char c;
	scanf("%x%c%x",&a,&c,&b);
	if(c=='+') sum=a+b;
	if(c=='-') sum=a-b;
	printf("%o\n",sum);
 } 
