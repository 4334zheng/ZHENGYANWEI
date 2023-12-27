#include<stdio.h>
int main()
{
	int a,b,d;
	char c;
	int x=1;
	scanf("%d%c%d=%d",&a,&c,&b,&d);
	printf("%d%c%d=%d ",a,c,b,d);
	if(c=='+'){
		if(a+b==d) printf("correct\n");
		else printf("wrong\n");
		x=0;
	}
	if(c=='-'){
		if(a-b==d) printf("correct\n");
		else printf("wrong\n");
		x=0;
	}
	if(c=='*'){
		if(a*b==d) printf("correct\n");
		else printf("wrong\n");
		x=0;
	}
	if(c=='/'){
		if(b!=0&&a/b==d&&a%b==0) printf("correct\n");
		else printf("wrong\n");
		x=0;
	}
    if(c=='%'){
		if(b!=0&&a%b==d) printf("correct\n");
		else printf("wrong\n");
		x=0;
    }
    
	if(x==1) printf("error op\n");
	return 0;
 } 
