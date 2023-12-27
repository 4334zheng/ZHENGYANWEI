#include<stdio.h>
int main()
{
	double c;
	int a,b;
	scanf("%d%d",&a,&b);
	c=(b*1.0/a)*100;
	printf("%.3f%%\n",c);
	return 0;
}
