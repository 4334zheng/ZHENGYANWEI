#include<stdio.h>
int main()
{
	double h,n;
	scanf("%lf %lf",&h,&n);
	int i=1;
	double x=0,H;
	H=h;
	x=h/2;
	for(i=1;i<n;i++)
	{
		H=H/2;
		H=(int)((H*1000+5)/10)/100.0;
		h=h+H*2;
		x/=2;
		x=(int)((x*1000+5)/10)/100.0;
	}
	printf("%.2f\n%.2f\n",h,x);
	return 0;
 } 
