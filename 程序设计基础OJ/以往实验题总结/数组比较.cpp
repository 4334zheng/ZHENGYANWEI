#include<stdio.h>

int main()
{
	int a[10],b[10];
	int i,j;
	for(i=0;i<10;i++)
	{
		scanf("%d",&a[i]);
	}
	for(j=0;j<10;j++)
	{
		scanf("%d",&b[j]);
	}
	int num1=0,num2=0;
	for(i=0;i<10;i++)
	{
		if(a[i]>b[i]) num1++;
		if(a[i]<b[i]) num2++;
	}
	if(num1>num2) printf("a>b\n");
	else if(num1<num2) printf("a<b\n");
	else printf("a=b\n");
	return 0;
}
