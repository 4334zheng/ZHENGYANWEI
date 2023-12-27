#include<stdio.h>
int main()
{
	int n,m,a,b;
	while((scanf("%u %u",&n,&m))!=EOF)
	{
		a=n;
		b=m;
		int num1,num2;
		while(a!=0&&b!=0)
		{
			if(a>=2*b)
			{
				num1=a/(2*b);
				a=a-num1*2*b;
				continue;
			 } 
			else if(b>=2*a) 
			{
				num2=b/(2*a);
				b=b-num2*2*a;
				continue;
			}
			else break;	
		}
		printf("%d %d\n",a,b);
	}
	return 0;
 } 
