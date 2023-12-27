#include<stdio.h>
#include<math.h>
int main()
{
	double a,b,c,s,A;
	int x,x1,y,y1,z,z1;
	int n,i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lf %lf %lf",&a,&b,&c);
		s=(a+b+c)/2;
		s=s*(s-a)*(s-b)*(s-c);
		if(s>0&&a>0&&b>0&&c>0)
		{
			A=sqrt(s);
	    	if(fabs(a-b)<0.001||fabs(a-c)<0.001||fabs(b-c)<0.001)
	    	{
	    		if(fabs(a-b)<0.001&&fabs(b-c)<0.001) printf("equilateral triangle, %.1f\n",A);
	    	    else if(fabs(a*a+b*b-c*c)<0.001||fabs(b*b+c*c-a*a)<0.001||fabs(a*a+c*c-b*b)<0.001)
		    	    printf("isosceles right triangle, %.1f\n",A);
		        else printf("isosceles triangle, %.1f\n",A);
	    		
		
	    	}
	     	else if(fabs(a*a+b*b-c*c)<0.001||fabs(b*b+c*c-a*a)<0.001||fabs(a*a+c*c-b*b)<0.001)
	    	printf("right triangle, %.1f\n",A);
	    	else printf("general triangle, %.1f\n",A);
      	} 
    	else printf("no triangle\n");
	}
	return 0;
}
