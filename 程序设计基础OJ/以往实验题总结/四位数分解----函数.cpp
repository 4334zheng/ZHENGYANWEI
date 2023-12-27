#include<stdio.h>

int add(int a,int b[4])
{
	b[0]=a/1000;
	b[1]=a%1000/100;
	b[2]=a%100/10;
	b[3]=a%10;
	int i;
	for(i=0;i<4;i++)
	{
		printf("%d ",b[i]);
	}
}

int main()
{
	int a;
	int b[4];
	scanf("%d",&a);
	add(a,b);
	return 0;
}
