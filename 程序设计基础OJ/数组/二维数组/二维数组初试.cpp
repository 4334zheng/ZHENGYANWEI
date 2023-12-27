#include<stdio.h>
int main()
{
	int i,j,a[2][3];
	for(i=0;i<2;i++)
	for(j=0;j<3;j++)
	scanf("%d",&a[i][j]);
	for(i=0;i<2;i++)
	for(j=0;j<3;j++)
	printf("%d ",a[i][j]);
	return 0;
 } 
