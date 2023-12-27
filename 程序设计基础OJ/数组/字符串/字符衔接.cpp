#include<stdio.h>
#include<string.h>
int main()
{
	int T,t;
	scanf("%d",&T);
	for(t=1;t<=T;t++)
	{
		char str1[100],str2[100];
		scanf("%s\n%s",str1,str2);
		int len1,len2;
		len1=strlen(str1);
		len2=strlen(str2);
		if(len1>3&&len2>3)
		{
			int i,j,i1,j1;
			char str3[10]={0},str4[4]={0};
			for(i=0,i1=0;i<3;i++,i1++)
			{
				str3[i1]=str1[i];
			}
			for(j=len2-1,j1=2;j>=len2-3;j--,j1--)
			{
				str4[j1]=str2[j];
			}
			
			strcat(str3,str4);
			printf("%s\n",str3);
		}
	} 
	return 0;
} 
