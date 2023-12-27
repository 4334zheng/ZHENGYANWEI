#include<stdio.h>
int main()
{
	int a,b,sum;
	char c;
	int T;
	scanf("%d",&T);
	int i;
	for(i=1;i<=T;i++)
	{
		scanf("%x%c%x",&a,&c,&b);
		if(c=='+') sum=a+b;
		if(c=='-') sum=a-b;
		printf("%o\n",sum);
	}
	return 0;
}
