#include<stdio.h>
int main()
{
	int a,b,x,y,z,sum;
	scanf("%d %d",&a,&b);
	while(a<=b){
		x=a/100;
		y=a%100/10;
		z=a%10;
		sum=x*x*x+y*y*y+z*z*z;
		if(sum==a) printf("%d\n",a);
		a++;
	}
	return 0;
}
