#include<stdio.h>
#include<conio.h>
#include<ctype.h> 
int main()
{
	char ch;
	ch=getch();
	if(toupper(ch)!='Y')
	return 0;
	printf("YES!\n");
}
