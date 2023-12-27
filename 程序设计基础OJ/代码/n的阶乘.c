#include<stdio.h>
int main()
{
	int n,b;
	int a=1;
	scanf("%d",&n);
	for(b=1;b<=n;b++){
		a=a*b;
	}
	printf("%d!=%d\n",n,a);
	return 0;
}
