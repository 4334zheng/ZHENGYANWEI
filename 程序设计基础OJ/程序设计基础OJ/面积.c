#include<stdio.h>
#include<math.h>
int main()
{
	double r,Area,b=3.1415926;
	int n;
	scanf("%lf,%d",&r,&n);
	Area=n*r*r*sin(2*b/n)/2;
	printf("Area=%.2f\n",Area);
	return 0; 
}
