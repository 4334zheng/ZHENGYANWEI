#include<stdio.h>
int main()
{
	int ch;
	int a=0,b=0,c=0,d=0;
    while((ch=getchar())!='\n')
	{
		if((ch>=65&&ch<=90)||(ch>=97&&ch<=122)) a++;
		else if(ch>='0'&&ch<='9') b++; 
		else if(ch==' ') c++;
		else d++;
	 } 
	 printf("%d %d %d %d\n",a,b,c,d);
	 return 0;
	
 } 
