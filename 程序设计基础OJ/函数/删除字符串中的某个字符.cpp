#include<stdio.h>
#include<string.h>

int del_char(char a[],char ch)
{
	int len;
	len=strlen(a);
	int i,j;
	for(i=0;i<len;i++)
	{
		if(a[i]==ch)
		{
			for(j=i;j<len;j++)
			{
				a[j]=a[j+1];
			}
		}
	} 
	printf("%s\n",a);
	return(a[len]);
} 

int main()
{
	char a[100];
	char ch;
	scanf("%c\n",&ch);
	scanf("%s",a);
	del_char(a,ch);
	return 0;
}
