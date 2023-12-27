#include<stdio.h>
#include<string.h>

int main()
{
	int n;
	scanf("%d",&n);
	char c[n][100];
	double num[n],t; 
	int i,j;
	for(i=0;i<n;i++)
	{
		scanf("%s%lf",c[i],&num[i]);
	}
	char s[100];
	for(i=1;i<n;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(num[j]<num[j+1])
			{
				t=num[j];
				num[j]=num[j+1];
				num[j+1]=t;
				strcpy(s,c[j]);
				strcpy(c[j],c[j+1]);
				strcpy(c[j+1],s);
			}
		}
	}
	for(i=0;i<n;i++)
	{
		printf("%s %gÍòÈË\n",c[i],num[i]);
	}
	return 0;
}
