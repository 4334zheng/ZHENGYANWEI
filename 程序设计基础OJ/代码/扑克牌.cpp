#include<stdio.h>
int main()
{
	char ch;
	int a;
	scanf("%c %d",&ch,&a);
	switch(ch)
	{
		case'A':
		case'a':printf("ºÚÌÒ");break;
		case'B':
		case'b':printf("ºìÌÒ");break;
		case'C':
		case'c':printf("Ã·»¨");break;
		case'D':
		case'd':printf("·½¿é");break; 
	}
	switch(a)
	{
		case 1:printf("A\n");break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:printf("%d\n",a);break;
		case 11:printf("J\n");break;
		case 12:printf("Q\n");break;
		case 13:printf("K\n");break;
	}
	return 0;
 } 
