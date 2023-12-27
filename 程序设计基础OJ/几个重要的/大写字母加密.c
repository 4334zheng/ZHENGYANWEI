#include<stdio.h>
int main()
{
	char ch,ch1;
	scanf("%c",&ch);
	ch1='A'+(ch-'A'+4)%26;
	printf("%c\n",ch1);
	return 0; 
 } 
