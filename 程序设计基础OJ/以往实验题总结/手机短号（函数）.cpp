#include<stdio.h>
#include<string.h>

int judge(char s[4])
{
	char str[18][4]={"134","135","136","137","138","182","183","184","133","153","180","181","189","130","131","132","155","156"};
	int i;
	for(i=0;i<18;i++)
	{
		if(strcmp(s,str[i])==0)
		{
			return 1;
		} 
	}
	return 0;
}

int main()
{
	int t;
	scanf("%d\n",&t);
	while(t--)
	{
		char str[15],s[4];
		int i;
		scanf("%s",str);
		for(i=0;i<3;i++)
		{
			s[i]=str[i];
		}
		s[3]='\0';
		if(judge(s))
		{
			char c='6';
			printf("%c",c);
			printf("%s",&str[6]);
			printf("\n");
		} 
		else printf("error\n");
	} 
	return 0;
}
