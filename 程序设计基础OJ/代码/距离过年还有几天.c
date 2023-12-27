#include<stdio.h>
int main()
{
	int a,b,c,d;
	scanf("%d %d %d",&a,&b,&c);
	if(b>2&&b!=7) d=(12-b)*30+30-c+(12-b)/2+1;
	if((a%100!=0&&a%4==0)||a%400==0)
	{
		if(b==1) d=31-c+366-31;
		if(b==2) d=29-c+366-29-31;
	}
	else 
	{
		if(b==1) d=31-c+365-31;
		if(b==2) d=28-c+365-28-31;
	}
	if(b==7) d=31-c+3*31+2*30;
	printf("%d\n",d);
	return 0;
 } 
