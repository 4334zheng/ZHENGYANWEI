#include<stdio.h>
#include<math.h>
int main()
{
	double a,b,c;
	scanf("%lf\n%lf\n%lf",&a,&b,&c);
	if(a+b>c&&b+c>a&&a+c>b)
	{
		if(fabs(a-b)<0.001||fabs(a-c)<0.001||fabs(b-c)<0.001)
		{
			if(a==b&&b==c)
		    printf("等边三角形\n");
		    else
			{
		    	if(fabs(a*a+b*b-c*c)<0.001||fabs(b*b+c*c-a*a)<0.001||fabs(a*a+c*c-b*b)<0.001)
			    printf("等腰直角三角形\n");
			    else printf("等腰三角形\n");
			}
		
		}
		else printf("普通三角形\n");
	} 
	else printf("非三角形\n");
	 return 0;
}
