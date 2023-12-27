#include<stdio.h>
int func()
{
	static int j=0;
	//auto int j=0;
	++j;
	printf("%-2d",j); 
} 

int main()
{
	int i;
	int func();
	for(i=1;i<=5;i++)
	func();
	return 0;
}
