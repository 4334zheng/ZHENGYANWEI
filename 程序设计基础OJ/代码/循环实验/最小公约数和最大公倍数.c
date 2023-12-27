#include<stdio.h>
int main()
{
	int a,b,r;
	scanf("%d %d",&a,&b);
	int t=1;
	while(t>0)
	{
		if(t%a==0&&t%b==0) break;
		else t++;
	}
	while(b!=0)
	{
		r=a%b;
		a=b;
		b=r;
	}
	printf("%d %d\n",a,t);
	return 0;
 } 
