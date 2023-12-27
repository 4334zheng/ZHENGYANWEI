#include<stdio.h>

int main()
{
	int a[10];
	int i;
	int sum=0;
	for(i=0;i<10;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	int num=0;
	for(i=0;i<10;i++)
	{
		if(a[i]>(sum/10)) num++;
	}
	printf("%d\n",num);
	return 0;
}
