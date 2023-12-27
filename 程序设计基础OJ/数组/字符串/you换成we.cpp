#include<stdio.h>
#include<string.h>
int main()
{
	char s[100][100];
	char ch;
	int i=0,j=0;
	while((ch=getchar())!=EOF) 
	{
		s[i][j++]=ch;
		if(ch==' ')
		{
			s[i][j]='\0';
			i++;
			j=0; 
		} 
		if(ch=='\n')
		{
			s[i][j]='\0';
			char c[200];
			c[0]='\0';
			int k=i;
			for(k=0;k<=i;k++)
			{
				if(strcmp(s[k],"you ")==0) strcat(c,"we ");
				else if(strcmp(s[k],"you")==0) strcat(c,"we");
				else strcat(c,s[k]);
			}
			printf("%s",c);
		}
	}
	return 0;
} 
