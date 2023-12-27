#include<stdio.h>
#include<math.h>
int main()
{
	double a,b,c,x1,x2,delt,x0,d;
	scanf("%lf %lf %lf",&a,&b,&c);
	delt=b*b-4*a*c;
	d=sqrt(delt)/(2*a);
	x0=(-b)/(2*a); 
    if(delt>=0)
    {
    	x1=x0+d;
    	x2=x0-d;
    	printf("x1=%f x2=%f\n",x1,x2);
	}
	else
	{
		d=sqrt(4*a*c-b*b)/(2*a);
		printf("x1=%.3f+%.3fi x2=%.3f-%.3fi\n",x0,d,x0,d);
	}
	return 0;
}
