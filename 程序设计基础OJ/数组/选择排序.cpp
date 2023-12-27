#include<stdio.h>
int main()
{
	int a[7],i,j,k,x;
	printf("Input 7 numbers:");
	for(i=0;i<7;i++)
	scanf("%d",&a[i]);
	printf("\n");
	for(i=0;i<6;i++)
	{
		k=i;
		for(j=i+1;j<=6;j++)
		{
			if(a[j]<a[k]) k=j;
		}
		if(k!=i) {
			x=a[i];
			a[i]=a[k];
			a[k]=x;
		}
	}
	for(i=0;i<7;i++)
	printf("%d ",a[i]);
	return 0;
	
}
