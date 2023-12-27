#include<stdio.h>
int main()
{
	int i,j;
	for(i=1;i<10;i++)
	printf("%4d",i);
	printf("\n-------------------------------------------\n");
	for(i=1;i<10;i++)
	for(j=1;j<10;j++)
	printf((j==9)?"%4d\n":"%4d",i*j);
 } 
