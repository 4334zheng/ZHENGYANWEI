#include<stdio.h>
int print(int w)
{
	int i;
	if(w!=0)
	{
		print(w-1);
		for(i=0;i<w;++i)
		{
			printf("%d ",w);
		}
		printf("\n");
	}
} 
int main()
{
	print(3);
	return 0;
}
