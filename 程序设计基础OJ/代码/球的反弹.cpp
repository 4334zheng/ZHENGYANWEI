#include<stdio.h>
int main()
{
	double h,n;
	double x,H;
	scanf("%lf %lf",&h,&n);
	int i=1;
	H=h;
	x=h/2;
	while(i<n)
	{
		h=h/2;
		h=(int)((h*1000+5)/10)/100.0;
		H=H+h*2;
		x=x/2;
		x=(int)((x*1000+5)/10)/100.0; 
		i++;
	}
	printf("%.2f\n%.2f\n",H,x);
	return 0;
}
