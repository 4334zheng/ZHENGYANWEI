#include<stdio.h>
#include<math.h>
int main()
{
	int g,cost;
	char ch;
	scanf("%d %c",&g,&ch);
	if(g<=1000)
	{
		if(ch=='y') cost=13;
		if(ch=='n') cost=8;
	}
	else
	{
		if(ch=='y')
		{
			if(g%500==0) cost=((g-1000)/500*4+13);
			else cost=((g-1000)/500*4+4+13);
		}
		if(ch=='n')
		{
		    if(g%500==0) cost=((g-1000)/500*4+8);
			else cost=((g-1000)/500*4+4+8);
		}
	}
	printf("%d\n",cost); 
	return 0;
 } 
