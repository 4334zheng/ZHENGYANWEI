#include<stdio.h>
#define NUM 10 
int main()
{
	int x;
	int count[NUM];
	int i;
	for(i=0;i<NUM;i++)
	{
		count[i]=0;
	}
	scanf("%d",&x);
	while(x!=-1)
	{
		if(x>=0&&x<=9) count[x]++;
		scanf("%d",&x); 
	}
	for(i=0;i<NUM;i++)
	{
		printf("%d:%d\n",i,count[i]);
	}
	return 0;
}
