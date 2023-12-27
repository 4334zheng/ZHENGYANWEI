#include<stdio.h>
int main()
{
	int N;
	int a=1;
	scanf("%d",&N);
	N=N-1;
	while(N>=1)
	{
		a=a*2+2;
		N--;
	}
	printf("%d\n",a);
	return 0;
}
