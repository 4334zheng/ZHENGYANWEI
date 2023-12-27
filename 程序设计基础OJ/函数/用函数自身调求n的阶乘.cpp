#include<stdio.h>
long fact(int n)
{
	long L;
	if(n==1) return 1;
	else{
		L=n*fact(n-1);
		return L;
	}
} 
int main()
{
	int x;
	scanf("%d",&x);
	long L;
	L=fact(x);
	printf("%ld",L);
	return 0;
}
