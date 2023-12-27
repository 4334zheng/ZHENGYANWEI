#include<stdio.h>
int main()
{
	char c;
	int a=1;
	scanf("%c",&c);
	if(48<=c&&c<=57){
		printf("digit\n");
		a=0;
	}
	if(65<=c&&c<=96){
		printf("upper\n");
		a=0;
	}
	if(97<=c&&c<=122){
		printf("lower\n");
		a=0;
	}
	if(a==1)printf("others\n");
	return 0;
 } 
