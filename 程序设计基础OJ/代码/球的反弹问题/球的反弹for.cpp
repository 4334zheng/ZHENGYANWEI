#include<stdio.h>
int main()
{
	double h,n;
	scanf("%lf%lf",&h,&n);
	int i=1;
	double x=0,H;
	H=h;
	
	for(i=1;i<n;i++)
	{
		x=(int)((h*500+5)/10)/100.0;
		H+=x*2;
		h=x;
	}
	x/=2;
	
	printf("%.2f\n%.2f\n",H,x);
	return 0;
 } 
