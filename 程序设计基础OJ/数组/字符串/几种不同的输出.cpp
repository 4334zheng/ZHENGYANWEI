#include<stdio.h>
int main()
{
	char name[]="John Smith";
	printf("The name is:%s\n",name);
	printf("Last name is:%s\n",&name[5]);
	printf("First name is:%s\n","John");
	return 0;
}
