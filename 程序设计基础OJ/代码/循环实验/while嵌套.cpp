#include<stdio.h>
int main()
{
	int i,j;
	i=1;
	while(i<=9)
	{
		j=1;
		while(j<=9)
		{
			printf("%d*%d=%d\n",i,j,i*j);
			j++; 
		}
		i++;
	}
	return 0;
}
