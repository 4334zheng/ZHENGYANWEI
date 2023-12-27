#include<stdio.h>
#include<string.h>

int main()
{
	int t,T;
	scanf("%d\n",&T);
	for(t=1;t<=T;t++)
	{
		int n;
		scanf("%d\n",&n);
		char str[n][20];
		int i;
		for(i=0;i<n;i++)
		{
			scanf("%s",str[i]);
		}
		int j;
		char s[20];
		for(i=1;i<n;i++)
		{
			for(j=0;j<n-i;j++) 
			{
				if(strcmp(str[j],str[j+1])==-1) 
				{
					strcpy(s,str[j]);
					strcpy(str[j],str[j+1] );
					strcpy(str[j+1] ,s);
				} 
			} 
		} 
		for(i=0;i<n-1;i++)
		{
			printf("%s ",str[i]);
		}
		printf("%s",str[n-1]);
		printf("\n");
	}
	return 0;
}
