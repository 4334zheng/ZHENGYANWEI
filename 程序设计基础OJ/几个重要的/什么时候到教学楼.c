#include<stdio.h>
int main()
{
	int h,m,s;
	scanf("%d:%d:%d",&h,&m,&s);
	h=(h+(m+(s+15)/60+20)/60)%24;
	m=(m+(s+15)/60+20)%60;
	s=(s+15)%60;
	printf("%d:%d:%d\n",h,m,s);
	return 0;
 } 
