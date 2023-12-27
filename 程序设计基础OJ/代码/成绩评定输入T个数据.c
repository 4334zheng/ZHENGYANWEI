#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i;
	scanf("%d",&i);
	double*a;
	a=(double*)malloc(i*sizeof(double));
	int b;
	for(b=0;b<i;b++){
		scanf("%lf",&a[b]);
	}
	for(b=0;b<i;b++)
	{
		if(a[b]>=85)printf("A\n");
		if(a[b]>=75&&a[b]<85)printf("B\n");
		if(a[b]>=65&&a[b]<75)printf("C\n");
		if(a[b]>=60&&a[b]<65)printf("D\n");
		if(a[b]<60)printf("F\n");
	 } 
	 free(a);
	return 0;
}
