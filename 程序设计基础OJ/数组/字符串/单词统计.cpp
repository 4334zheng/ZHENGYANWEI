#include<stdio.h>
#include<string.h>
int main()
{
	int i=0,j=0,a[100]={0};
	char s[100][100],s1[100];
	while(1)
	{
		scanf("%s",s1);
		if(strcmp(s1,"0")==0) break;
		for(j=0;j<i;j++)
		{
			if(strcmp(s[j],s1)==0) break;
		}
		if(j==i) strcpy(s[i++],s1),a[j]++;
		else a[j]++; 
	}
	int k=i,c;
	for(i=0;i<k;i++)
	{
		for(j=0,c=0;j<k;j++)
		{
			if(a[c]<a[j]) c=j;
		}
		printf("%d %s\n",a[c],s[c]);
		a[c]=0;
	}
	return 0;
}
