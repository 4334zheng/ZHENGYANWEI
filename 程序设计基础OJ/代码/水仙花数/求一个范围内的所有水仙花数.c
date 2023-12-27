#include<stdio.h>
int main()
{
	int a,b,c,d;
	scanf("%d %d",&a,&b);
	for(;a<=b;a++){
		c=a;
		int sum=0;
		for(;c!=0;c=c/10){
			d=c%10;
			sum=sum+d*d*d;
		}
		if(sum==a) printf("%d\n",a);
	} 
	return 0;
 } 
